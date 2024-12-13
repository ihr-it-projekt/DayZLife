class DZLFractionListener: DZLBaseEventListener {
    DZLDatabaseLayer database;

    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        database = DZLDatabaseLayer.Get();;
        DZLFraction fraction;
        DZLPlayer dzlPlayer;
        if(rpc_type == DZL_RPC.GET_FRACTION) {
            dzlPlayer = database.Get().GetPlayer(sender.GetId());
            array<ref DZLFractionMember> notMembers;
            if(dzlPlayer.IsFractionBoss()) {
                fraction = database.GetFraction(sender.GetId());
                notMembers = GetPlayerNotInFractionCollection(fraction);
                g_Game.RPCSingleParam(null, DZL_RPC.GET_FRACTION_RESPONSE_FRACTION_OWNER, new Param2<ref DZLFraction, ref array<ref DZLFractionMember>>(fraction, notMembers), true, sender);
            } else if(dzlPlayer.IsInAnyFraction()) {
                g_Game.RPCSingleParam(null, DZL_RPC.GET_FRACTION_RESPONSE_FRACTION_MEMBER, new Param1<ref DZLFractionMember>(dzlPlayer.GetFractionMember()), true, sender);
            } else {
                array<ref DZLFractionMember> potentialFractions = new array<ref DZLFractionMember>;
                array<string> ids = dzlPlayer.GetFractionIdsWherePlayerCanJoin();

                foreach(string id: ids) {
                    fraction = database.GetFraction(id);

                    if(fraction) {
                        potentialFractions.Insert(new DZLFractionMember(id, sender.GetId(), "", fraction.GetName(), false));
                    }
                }

                g_Game.RPCSingleParam(null, DZL_RPC.GET_FRACTION_RESPONSE_NOT_A_FRACTION_MEMBER, new Param1<ref array<ref DZLFractionMember>>(potentialFractions), true, sender);
            }
        } else if(rpc_type == DZL_RPC.GET_UPDATE_FRACTION_MEMBERS) {
            dzlPlayer = database.Get().GetPlayer(sender.GetId());
            if(dzlPlayer.IsFractionBoss()) {
                Param2<ref array<ref DZLFractionMember>, ref array<ref DZLFractionMember>> fractionMembers;
                if(ctx.Read(fractionMembers)) {
                    fraction = database.GetFraction(sender.GetId());

                    if(fraction) {
                        ref array<ref DZLFractionMember>members = fraction.GetMembers();
                        ref array<ref DZLFractionMember>potentialMembers = fraction.GetPotentialMembers();
                        ref array<ref DZLFractionMember>newMembersFromRequest = fractionMembers.param1;
                        ref array<ref DZLFractionMember>newPotentialMembersFromRequest = fractionMembers.param2;

                        HandleRemoveMembers(members, newMembersFromRequest, fraction);
                        HandleRemovePotentialsMembers(potentialMembers, newPotentialMembersFromRequest, fraction);
                        HandleAddPotential(newPotentialMembersFromRequest, potentialMembers, fraction);
                        HandleUpdateMemberRights(newMembersFromRequest, fraction);
                    }

                    fraction.Save();
                }
            }

            g_Game.RPCSingleParam(null, DZL_RPC.GET_UPDATE_FRACTION_MEMBERS_RESPONSE, null, true, sender);
        } else if(rpc_type == DZL_RPC.DELETE_FRACTION) {
            dzlPlayer = database.Get().GetPlayer(sender.GetId());
            if(dzlPlayer.IsFractionBoss()) {
                database.RemoveFraction(sender.GetId());
                dzlPlayer.RemoveFraction(sender.GetId());
            }
            g_Game.RPCSingleParam(null, DZL_RPC.DELETE_FRACTION_RESPONSE, null, true, sender);
        } else if(rpc_type == DZL_RPC.FRACTION_MEMBER_LEAVE) {
            dzlPlayer = database.Get().GetPlayer(sender.GetId());
            if(!dzlPlayer.IsFractionBoss() && dzlPlayer.IsInAnyFraction()) {
                fraction = dzlPlayer.GetFraction();
                fraction.RemoveMember(sender.GetId());
                fraction.Save();
                dzlPlayer.RemoveFraction(fraction.GetId());
            }

            g_Game.RPCSingleParam(null, DZL_RPC.FRACTION_MEMBER_LEAVE_RESPONSE, null, true, sender);
        } else if(rpc_type == DZL_RPC.FRACTION_MEMBER_JOIN) {
            dzlPlayer = database.Get().GetPlayer(sender.GetId());
            Param1<ref DZLFractionMember> fractionMemberToJoinParam;
            if(ctx.Read(fractionMemberToJoinParam)) {
                if(!fractionMemberToJoinParam.param1) return;
                DZLFractionMember fractionMemberToJoin = fractionMemberToJoinParam.param1;
                if(dzlPlayer.HasPotentialFraction(fractionMemberToJoin.fractionID) && !dzlPlayer.IsInAnyFraction()) {
                    fraction = database.GetFraction(fractionMemberToJoin.fractionID);
                    fraction.RemovePotentialMember(sender.GetId());
                    fraction.AddMember(new DZLFractionMember(fraction.GetId(), sender.GetId(), dzlPlayer.playerName, fraction.GetName(), true));
                    fraction.Save();

                    dzlPlayer.SetFraction(fraction);
                }
            }

            g_Game.RPCSingleParam(null, DZL_RPC.FRACTION_MEMBER_JOIN_RESPONSE, null, true, sender);
        } else if(rpc_type == DZL_RPC.FRACTION_CREATE_FRACTION) {
            dzlPlayer = database.Get().GetPlayer(sender.GetId());
            Param1<string> createFractionParam;
            if(ctx.Read(createFractionParam)) {
                if(!dzlPlayer.IsInAnyFraction()) {
                    fraction = new DZLFraction(sender.GetId(), createFractionParam.param1);
                    DZLFractionMember boss = new DZLFractionMember(sender.GetId(), sender.GetId(), dzlPlayer.playerName, createFractionParam.param1, true);
                    boss.canAccessBankAccount = true;
                    boss.canGetMoneyFromBankAccount = true;
                    boss.canAccessFractionGarage = true;

                    fraction.AddMember(boss);
                    fraction.Save();

                    dzlPlayer.SetFraction(fraction);
                }

                g_Game.RPCSingleParam(null, DZL_RPC.FRACTION_MEMBER_JOIN_RESPONSE, null, true, sender);
            }
        }
    }

    private void HandleAddPotential(ref array<ref DZLFractionMember> newPotentialMembers, ref array<ref DZLFractionMember> oldPotet, DZLFraction fraction) {
        foreach(DZLFractionMember member: newPotentialMembers) {
            member.isMember = false;
            fraction.AddPotentialMember(member);
            DZLPlayer currentPlayer = database.GetPlayer(member.playerId);
            currentPlayer.AddPotentialFraction(fraction.GetId());
        }
    }

    private void HandleRemoveMembers(ref array<ref DZLFractionMember> members, ref array<ref DZLFractionMember> membersToCompare, DZLFraction fraction) {
        foreach(DZLFractionMember member: members) {
            if(member.IsFractionBoss()) continue;
            bool hasFound = false;
            foreach(DZLFractionMember memberToCompare: membersToCompare) {
                if(memberToCompare.playerId == member.playerId) {
                    hasFound = true;
                    break;
                }
            }
            if(false == hasFound) {
                DZLPlayer currentPlayer = database.GetPlayer(member.playerId);
                currentPlayer.RemoveFraction(fraction.GetId());
                fraction.RemoveMember(member.playerId);
            }
        }
    }

    private void HandleUpdateMemberRights(ref array<ref DZLFractionMember> members, DZLFraction fraction) {
        foreach(DZLFractionMember member: members) {
            fraction.UpdateMember(member);
            DZLPlayer player = database.GetPlayer(member.playerId);

            player.UpdateFraction(fraction);
        }
    }

    private void HandleRemovePotentialsMembers(ref array<ref DZLFractionMember> members, ref array<ref DZLFractionMember> membersToCompare, DZLFraction fraction) {
        foreach(DZLFractionMember member: members) {
            bool hasFound = false;
            foreach(DZLFractionMember memberToCompare: membersToCompare) {
                if(memberToCompare.playerId == member.playerId) {
                    hasFound = true;
                    break;
                }
            }
            if(false == hasFound) {
                DZLPlayer currentPlayer = database.GetPlayer(member.playerId);
                currentPlayer.RemovePotentialFraction(fraction.GetId());
                fraction.RemovePotentialMember(member.playerId);
            }
        }
    }

    private array<ref DZLFractionMember> GetPlayerNotInFractionCollection(DZLFraction fraction) {
        array<ref DZLFractionMember> collection = new array<ref DZLFractionMember>;
        ref array<string> playerIdentities = DZLDatabaseLayer.Get().GetPlayerIds().playerIdentities;
        foreach(string ident: playerIdentities) {
            DZLPlayer player = DZLDatabaseLayer.Get().GetPlayer(ident);
            player.GetFraction();
            if(!player.IsInAnyFraction() && !fraction.HasPotentialMember(ident)) {
                collection.Insert(new DZLFractionMember("", ident, player.playerName, "", false));
            }
        }

        return collection;
    }
}
