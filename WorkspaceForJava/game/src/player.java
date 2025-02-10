class player {
    private String name;// プレイヤー名を記憶する
    private Strategy strategy;// 戦略のインスタンス
    private int wincount;// 勝った回数を記憶する
    private int losecount;// 負けた回数を記憶する
    // プレイヤーをインスタンス化するときに，名前と戦略を決める

    player(String name, Strategy strategy) {
        this.name = name;
        this.strategy = strategy;
    }

    // i 回戦の対戦カードを出す
    public int nextNumber(int i) {
        return strategy.nextNumber(i);
    }

    // 敵が出したカードの数を渡される
    public void learning(int enemy) {
        strategy.learning(enemy);
    }

    // 勝ったら勝ち回数をインクリメントする
    public void win() {
        wincount++;
    }

    // 負けたら負け回数をインクリメントする
    public void lose() {
        losecount++;
    }

    // 呼ばれたときの勝ち数と負け数の文字列を返す
    public String toString() {
        return (wincount + "勝" + losecount + "敗");
    }

    // プレイヤーの名前を返す
    public String getName() {
        return name;
    }
}