class DZLRankHelper {
    static DZLPaycheck getCurrentPayCheck(DZLPlayer dzlPlayer, DZLPaycheckConfig config) {
        if(dzlPlayer) {
            string jobName = dzlPlayer.GetActiveJob();

            array<ref DZLPaycheck> payChecks = config.GetPaycheckByJob(jobName);
            return searchPayCheck(dzlPlayer, payChecks);
        }

        return new DZLPaycheck("", "", 0, 999999);
    }

    private static DZLPaycheck searchPayCheck(DZLPlayer dzlPlayer, ref array<ref DZLPaycheck> payChecks) {
        DZLPaycheck defaultPaycheck = new DZLPaycheck("", "", 0, 999999);

        foreach(DZLPaycheck payCheck: payChecks) {
            if(dzlPlayer.IsActiveJobGrade(payCheck.rank) && payCheck.amount > 0) {
                return payCheck;
            }

            if(payCheck.isFallbackRank) {
                defaultPaycheck = payCheck;
            }
        }

        return defaultPaycheck;
    }
}