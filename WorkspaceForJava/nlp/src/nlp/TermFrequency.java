package nlp;

import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Comparator;

class WordCompare implements Comparator<WordCount> {
    @Override
    public int compare(WordCount wc1, WordCount wc2) {
        if (wc1.getCount() < wc2.getCount())
            return 1;
        if (wc1.getCount() == wc2.getCount())
            return 0;
        if (wc1.getCount() > wc2.getCount())
            return -1;
        return 0;
    }
}

public class TermFrequency {
    ArrayList<TfCount> list = new ArrayList<TfCount>();

    ArrayList<TfCount> getList() {
        return list;
    }

    public void tf(String inputFilename, String outputFilename) {
        try {
            FileWriter fw = new FileWriter(outputFilename);
            System.out.println("出力ファイル: " + outputFilename);

            String[] command = { "cmd.exe", "/C", "mecab", inputFilename };
            Process ps = Runtime.getRuntime().exec(command);

            BufferedReader bReader_i = new BufferedReader(new InputStreamReader(ps.getInputStream(), "SJIS"));
            String targetLine;
             this.list.clear();

            while ((targetLine = bReader_i.readLine()) != null) {
                if (targetLine.equals("EOS"))
                    continue;

                String[] targetArray = targetLine.split("[,\t]");
                Word wo = new Word();
                if (targetArray.length >= 1)
                    wo.setHyousoukei(targetArray[0]);
                if (targetArray.length >= 2)
                    wo.setHinshi(targetArray[1]);
                if (targetArray.length >= 3)
                    wo.setHinshi1(targetArray[2]);
                if (targetArray.length >= 4)
                    wo.setHinshi2(targetArray[3]);
                if (targetArray.length >= 5)
                    wo.setHinshi3(targetArray[4]);
                if (targetArray.length >= 6)
                    wo.setKatsuyoKata(targetArray[5]);
                if (targetArray.length >= 7)
                    wo.setKatsuyoKei(targetArray[6]);
                if (targetArray.length >= 8)
                    wo.setGenkei(targetArray[7]);
                if (targetArray.length >= 9)
                    wo.setYomi(targetArray[8]);
                if (targetArray.length >= 10)
                    wo.setHatsuon(targetArray[9]);

                boolean found = false;
                for (TfCount tfc : list) {
                    if (tfc.getWord().equals(wo)) {
                        tfc.setCount(tfc.getCount() + 1);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    list.add(new TfCount(wo, 1));
                }
            }

            // TF 計算
            int totalCount = 0;
            for (TfCount tfc : list) {
                totalCount += tfc.getCount();
            }
            for (TfCount tfc : list) {
                tfc.setTf((double) tfc.getCount() / totalCount);
            }

            // ソート
            list.sort(new WordCompare());
            // 出力
            fw.write("#語\t出現回数\tTF\n");
            for (TfCount tfc : list) {
                fw.write(tfc.getWord().getHyousoukei() + "\t" +
                        tfc.getCount() + "\t" +
                        String.format("%.10f", tfc.getTf()) + "\n");
            }

            fw.close();
            System.out.println("TF計算完了。出力しました。");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}