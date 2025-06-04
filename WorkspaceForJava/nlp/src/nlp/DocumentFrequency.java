package nlp;

import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Comparator;
import java.io.FileReader;

class DfComparator implements Comparator<DfCount> {
    @Override
    public int compare(DfCount o1, DfCount o2) {
        if (o1.getDf() < o2.getDf()) {
            return 1;
        } else if (o1.getDf() == o2.getDf()) {
            return 0;
        } else {
            return -1;
        }
    }
}

public class DocumentFrequency {
    // DF をカウントするためのデータ格納領域の定義
    ArrayList<DfCount> list = new ArrayList<DfCount>();

    // DF の元になる TF を受ける
    TermFrequency tf[];

    DocumentFrequency(TermFrequency[] tf) {
        this.tf = tf;
    }

    public void df(String outputFilename) {
        System.out.println("DF 導出");
        // TF100 ファイル分について繰り返す
        for (int i = 0; i < tf.length; i++) {
            int N = tf.length; // 全体のドキュメント数
            // TF1 件に含まれる語の分だけ繰り返し
            for (int j = 0; j < tf[i].list.size(); j++) {
                Word word = tf[i].list.get(j).getWord();
                Integer count = tf[i].list.get(j).getCount();

                // DF のリストの中にエントリがあるか調べる
                boolean found = false;
                for (DfCount dfCount : list) {
                    if (dfCount.getWord().equals(word)) {
                        // エントリがあったときは，DFとidfを更新する
                        dfCount.setDf(dfCount.getDf() + 1);
                        dfCount.setIdf(Math.log10(N / (double) dfCount.getDf()) + 1);
                        found = true;
                        break;
                    }
                }
                // エントリが無かったときは，新しい語としてリストに追加する
                if (!found) {
                    DfCount newDfCount = new DfCount(word, count, Math.log10(N) + 1, 1);
                    list.add(newDfCount);
                }
            }
        }
        System.out.println("DF の計算が完了しました。");
        // ソートする
        list.sort(new DfComparator());
        // df,idf の結果をファイルに保存する
        System.out.println("DF の結果をファイルに保存します。");
        System.out.println("出力ファイル: " + outputFilename);
        try {
            FileWriter fw = new FileWriter(outputFilename);
            for (DfCount dfc : list) {
                fw.write(dfc.getWord().getHyousoukei() + "\t" +
                        dfc.getDf() + "\t" +
                        dfc.getIdf() + "\n");
            }
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("出力ファイルの書き込みに失敗しました。");
        }
    }
}