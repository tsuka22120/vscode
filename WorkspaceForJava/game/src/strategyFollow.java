import java.util.ArrayList;
import java.util.List;

class strategyFollow implements Strategy {
    // 直前に相手が出した番号を記憶しておくフィールド
    private int preValue = 1;
    // 手持ちの札を覚えておくリスト
    private List<Integer> cards = new ArrayList<Integer>();

    strategyFollow() {
        cards.add(1);
        cards.add(2);
        cards.add(3);
        cards.add(4);
        cards.add(5);
    }

    @Override
    public Integer nextNumber(int i) {
        int returnValue = 1;
        if (cards.indexOf(preValue) != -1)// 出すカードがあるか調べる
        {// 該当のカードが手持ちにあれば，そのカードを出す
            returnValue = preValue;
        } else {// 該当するカードがない時には，0 番目にあるカードを出す
            returnValue = cards.get(0);
        }
        int index = cards.indexOf(returnValue);
        cards.remove(index);// 出した数字を削除する．数字は0 番から格納されている．
        return returnValue;
    }

    @Override
    public void learning(int enemyNumber) {// 出したカードを記憶しておく
        preValue = enemyNumber;
    }
}