# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

DayZLife is a **DayZ (Standalone) server mod** written in Enfusion "Enforce Script" (`.c` files). It turns a DayZ server into a role-play server: jobs (police, medic, army, civilian), banking, licences, vehicle keys/tuning, base building/raiding, a fraction (gang) system, trader shops, a ticket/arrest system, and an in-game message/mail system, all with client-side menus and a server-side admin "Almanac" panel.

Unlike some of the author's other mods, this one does **not** hard-depend on the external `TBLib` framework — it implements its own event-listener base class (`DZLBaseEventListener`) and its own RPC enum (`DZL_RPC`). It does optionally *integrate* with other mods by the same author (`TBLibClient`, `TBRevivePlayerClient/Server`, `TBRealEstateClient`) via preprocessor guards — see "Optional cross-mod integration" below.

## Repository layout

- `DayZLifeClient/` — client-side PBO source: `config.cpp` (`CfgPatches`/`CfgMods`, preloads `TBRealEstateClient`/`TBRevivePlayerClient`), `scripts/3_Game`, `scripts/4_World`, `scripts/5_Mission` (DayZ's standard script-module split), `layout/` (per-feature `.layout` GUI files, one subfolder per menu: Banking, Almanac, Arrest, CarKey, Garage, Licence, Tuning, Ticket, Trader, etc.), `model/` (p3d/config.cpp per custom item: ATM, Cement, Money, Ore, ParkingMeter, Terminal, jewelry), `Data/` (`Version.hpp`, `Credits.json`, sound), and `stringtable.csv`.
- `DayZLifeServer/` — server-side PBO source (mirrors the `3_Game`/`4_World`/`5_Mission` split, though most logic lives in `4_World`); depends on `DayZLifeClient` and `JM_CF_Scripts` (per `config.cpp`). Holds `EventListener/` (one class per feature, e.g. `DZLBankListener`, `DZLTraderListener`, `DZLPlayerArrestListener`), `Manager/` (`DZLEventManager`, `DZLBuilderManager`, `DZLInsuranceManager`), and `Logger/` (`DZLCSVLogger`).
- `DayZLifeClient/pbo/*.pbo`, `DayZLifeServer/pbo/*.pbo` — prebuilt packaging output, not sources to hand-edit.
- `Images/` — screenshots used in the project's external README/marketing page.
- `README.md` — points to the full docs at an external `DayZModsInfo` GitHub repo and describes the contribution workflow (fork, format with `astyle` using a specific flag set, open a PR).
- `todo.md` — outstanding work/ideas.
- `test/Main.java` — an unrelated scratch Java file; not part of the mod.

## Build, packaging, and "testing"

There is **no local build/lint/test tooling** — Enforce Script is compiled by the DayZ engine itself:

- Correctness is verified by loading the mod in a DayZ client/server (BI's DayZ Tools/Workbench or a running dev server), not a CLI command.
- `README.md` prescribes running `astyle` (a specific flag set: `--style=java --pad-comma --attach-return-type --mode=c ...`) over `*.cpp`/`*.c` before opening a PR — treat that as the project's formatting convention when editing script files.
- `.pbo` files under `pbo/` are prior packaging outputs, not sources.
- To validate a change without a compiler, check Enforce Script syntax/consistency by reading the code (matching braces, correct `modded class` usage and override signatures against the base game).

## Architecture notes

### Client/Server split & communication
Client and server are separate PBOs talking over DayZ's RPC system via the `DZL_RPC` enum (`DayZLifeClient/scripts/3_Game/RPC.c`), e.g. `PLAYER_DATA`/`PLAYER_DATA_RESPONSE`, `EVENT_GET_CONFIG`/per-topic `EVENT_GET_CONFIG_RESPONSE_*`, `TRADE_ACTION`, `ARREST_PLAYER`, `BUY_LICENCE`. Both sides derive their RPC listeners from the mod's own `DZLBaseEventListener` (`DayZLifeClient/scripts/4_World/Eventlistener/DZLBaseEventListener.c`), which just wires `OnRPC` into `GetDayZGame().Event_OnRPC` — server listeners live under `DayZLifeServer/scripts/4_World/EventListener/`, one per feature area, each overriding `OnRPC` and switching on `rpc_type`.

### `modded class` — extending the base game
Enforce Script's modding convention is used throughout: `modded class PlayerBase`, `modded class MissionServer`, `modded class MissionGameplay`, `modded class CarScript`, `modded class DayZGame`, etc. Expect a given base-game class's full behavior to be split across multiple `modded class` fragments in different files (e.g. `PlayerBase.c` for RP stats vs. `dayzplayercfgbase.c` for animation config).

### Config & persistence
Each feature has its own config singleton (`DZLBankingConfig`, `DZLHouseConfig`, `DZLJobConfig`, `DZLCarConfig`, `DZLCrimeConfig`, etc., under `scripts/4_World/Config/<Feature>/`), all following the same pattern seen in `DZLConfig.c`/`DZLBankingConfig.c`: lazy `Get()` singleton, `Load()`/`Save()` to a JSON file, and a **sequential string-version migration** in the constructor — `if(version == "1") { ...; version = "2"; Save(); } if(version == "2") { ...; version = "3"; Save(); }` and so on. When adding a persisted field, add a new `version == "N"` step rather than changing an existing default, so upgrades apply cleanly to existing server installs. The client-facing aggregate `DZLConfig` (extends `DZLBaseEventListener`) requests all per-topic configs from the server via `EVENT_GET_CONFIG` and assembles them from the various `EVENT_GET_CONFIG_RESPONSE_*` RPCs.

### Logging
`DZLCSVLogger` (`DayZLifeServer/scripts/4_World/Logger/DZLCSVLogger.c`, server-only) writes per-topic CSV files (`money_log.csv`, `trader_log.csv`, `crafting_log.csv`, ...) gated by flags on `DZLLoggerConfig`. New loggable actions should add a guarded `DZLLog...` function following this same head/data-row CSV pattern rather than ad hoc file output.

### UI
Client menus live under `DayZLifeClient/scripts/4_World/Menu/` (`DZLBankingMenu`, `DZLTraderMenu`, `DZLFractionMenu`, `DZLLicenceMenu`, `DZLCarMenu`, `DZLAlmanacMenu` — the admin panel — etc.), all building on a shared `DZLBaseMenu`, plus helpers in `Menu/Helper/` (`DZLUIItemCreator`, `DZLPreviewWindow`, `DZLDisplayHelper`). Layout files referenced by these menus live in `DayZLifeClient/layout/<Feature>/`.

### Optional cross-mod integration
Code guards optional integrations behind preprocessor flags, e.g. `#ifdef TBLibClient` (routes chat messages through `TBLibSendMessage` in `PlayerBase.c`), `#ifndef TBRevivePlayerServer` (skips this mod's own respawn RPC when that mod's revive flow is present, in `MissionServer.c`), and a similar guard around `TBRevivePlayerClient`/`TBRealEstateClient` at the `config.cpp` preload level. These are optional companions, not hard dependencies — don't assume they're present in every build.

### Localization
User-facing strings are looked up by key from `DayZLifeClient/stringtable.csv` (all language columns). Add new keys there rather than hardcoding display text in script.
