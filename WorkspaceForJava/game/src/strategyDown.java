public class strategyDown implements Strategy {
    // 配列の番号を出す順番として4 から0 の場所に格納されている5 から1 を順番に出す．
    private int[] cards = new int[5];

    strategyDown() {
        cards[0] = 5;
        cards[1] = 4;
        cards[2] = 3;
        cards[3] = 2;
        cards[4] = 1;
    }

    public Integer nextNumber(int i) {
        int value = cards[i];
        return value;
    }

    public void learning(int enemy) {
    }
}
