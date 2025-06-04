package nlp;

public class Word {
    private String hyousoukei = null;
    private String hinshi = null;
    private String hinshi1 = null;
    private String hinshi2 = null;
    private String hinshi3 = null;
    private String katsuyoKata = null;
    private String katsuyoKei = null;
    private String genkei = null;
    private String yomi = null;
    private String hatsuon = null;

    public String getHyousoukei() {
        return hyousoukei;
    }

    public void setHyousoukei(String hyousoukei) {
        this.hyousoukei = hyousoukei;
    }

    public String getHinshi() {
        return hinshi;
    }

    public void setHinshi(String hinshi) {
        this.hinshi = hinshi;
    }

    public String getHinshi1() {
        return hinshi1;
    }

    public void setHinshi1(String hinshi1) {
        this.hinshi1 = hinshi1;
    }

    public String getHinshi2() {
        return hinshi2;
    }

    public void setHinshi2(String hinshi2) {
        this.hinshi2 = hinshi2;
    }

    public String getHinshi3() {
        return hinshi3;
    }

    public void setHinshi3(String hinshi3) {
        this.hinshi3 = hinshi3;
    }

    public String getKatsuyoKata() {
        return katsuyoKata;
    }

    public void setKatsuyoKata(String katsuyoKata) {
        this.katsuyoKata = katsuyoKata;
    }

    public String getKatsuyoKei() {
        return katsuyoKei;
    }

    public void setKatsuyoKei(String katsuyoKei) {
        this.katsuyoKei = katsuyoKei;
    }

    public String getGenkei() {
        return genkei;
    }

    public void setGenkei(String genkei) {
        this.genkei = genkei;
    }

    public String getYomi() {
        return yomi;
    }

    public void setYomi(String yomi) {
        this.yomi = yomi;
    }

    public String getHatsuon() {
        return hatsuon;
    }

    public void setHatsuon(String hatsuon) {
        this.hatsuon = hatsuon;
    }

    public boolean equals(Object obj) {
        if (obj == null || !(obj instanceof Word))
            return false;
        Word other = (Word) obj;
        return (safeEquals(hyousoukei, other.hyousoukei)
                && safeEquals(hinshi, other.hinshi)
                && safeEquals(hinshi1, other.hinshi1)
                && safeEquals(hinshi2, other.hinshi2)
                && safeEquals(hinshi3, other.hinshi3)
                && safeEquals(katsuyoKata, other.katsuyoKata)
                && safeEquals(katsuyoKei, other.katsuyoKei)
                && safeEquals(genkei, other.genkei)
                && safeEquals(yomi, other.yomi)
                && safeEquals(hatsuon, other.hatsuon));
    }

    private boolean safeEquals(String s1, String s2) {
        if (s1 == null && s2 == null)
            return true;
        if (s1 == null || s2 == null)
            return false;
        return s1.equals(s2);
    }
}
