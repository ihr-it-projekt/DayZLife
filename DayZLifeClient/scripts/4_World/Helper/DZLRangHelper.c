class DZLRankHelper {
    static DZLPaycheck getCurrentPayCheck(DZLPlayer dzlPlayer, DZLPaycheckConfig config) {
        if(dzlPlayer) {
            if(dzlPlayer.IsActiveAsCop()) {
                return searchPayCheck(dzlPlayer, config.cops);
            }

            if(dzlPlayer.IsActiveAsTransport()) {
                return searchPayCheck(dzlPlayer, config.transports);
            }

            if(dzlPlayer.IsActiveAsMedic()) {
                return searchPayCheck(dzlPlayer, config.medics);
            }

            if(dzlPlayer.IsActiveAsArmy()) {
                return searchPayCheck(dzlPlayer, config.armies);
            }

            if(dzlPlayer.IsActiveAsCivil()) {
                return searchPayCheck(dzlPlayer, config.civils);
            }
        }

        return new DZLPaycheck("", "", 0, 10000000);
    }

    private static DZLPaycheck searchPayCheck(DZLPlayer dzlPlayer, ref array<ref DZLPaycheck> payChecks) {
        DZLPaycheck defaultPaycheck = new DZLPaycheck("", "", 0, 10000000);

        foreach(DZLPaycheck payCheck: payChecks) {
            if(dzlPlayer.HasJobGrade(payCheck.rank) && payCheck.amount > 0) {
                return payCheck;
            }

            if(payCheck.isFallbackRank) {
                defaultPaycheck = payCheck;
            }
        }

        return defaultPaycheck;
    }
}