class strategyStraight implements Strategy {
    // 配列の番号を出す順番として0 から4 の場所に格納されている1 から5 を順番に出す．
    private int[] cards = new int[5];

    strategyStraight() {
        cards[0] = 1;
        cards[1] = 2;
        cards[2] = 3;
        cards[3] = 4;
        cards[4] = 5;
    }

    @Override
    public Integer nextNumber(int i) {
        int value = cards[i];
        return value;
    }

    @Override
    public void learning(int enemy) {
    }
}