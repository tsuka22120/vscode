import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class strategyRandom implements Strategy {
        // 数値を格納するリストをつくる
        private List<Integer> cards = new ArrayList<Integer>();

        strategyRandom() {
                // リストに数値を順に入れていく
                cards.add(1);
                cards.add(2);
                cards.add(3);
                cards.add(4);
                cards.add(5);
                // コレクションのシャッフル機能を使ってシャッフルする
                Collections.shuffle(cards);//
        }

        // リストから順番に数値を出す
        public Integer nextNumber(int i) {
                return cards.get(i);
        }

        // 過去の出し手を利用しないので何も操作しない実装をする
        @Override
        public void learning(int enemy) {
        }
}