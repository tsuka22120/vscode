public class Main {
        public static void main(String args[]) {
                // プレイヤーをインスタンス化
                player player1 = new player("PC", new strategyRandom());
                player player2 = new player("P1", new strategyDown());
                System.out.println(player1.getName() + ":" + player2.getName());
                // 5 枚のカードで対戦する
                for (int i = 0; i < 5; i++) {
                        // カードの数字を出す
                        int player1Num = player1.nextNumber(i);
                        int player2Num = player2.nextNumber(i);
                        // カードの数字を表示する
                        System.out.println(player1Num + ":" + player2Num);
                        // 勝ち負けに応じて，成績を保存する
                        if (player1Num > player2Num) {
                                player1.win();
                                player2.lose();
                        } else if (player1Num < player2Num) {
                                player1.lose();
                                player2.win();
                        }
                        // 対戦相手のカードの数字を学習する
                        player1.learning(player2Num);
                        player2.learning(player1Num);
                }
                // 成績を表示する
                System.out.println(player1.getName() + ":" + player1);
                System.out.println(player2.getName() + ":" + player2);
        }
}