package nlp;

import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Comparator;

class tfIdfComparator implements Comparator<tfIdfCount> {
    @Override
    public int compare(tfIdfCount o1, tfIdfCount o2) {
        return Double.compare(o2.getTfidf(), o1.getTfidf());
    }
}

class termFrequency_inverseDocumentFrequency {
    ArrayList<tfIdfCount> list = new ArrayList<tfIdfCount>();
    TermFrequency tf;
    DocumentFrequency df;

    public termFrequency_inverseDocumentFrequency(TermFrequency tf, DocumentFrequency df) {
        this.tf = tf;
        this.df = df;
    }

    public void tfIdf(String outputFilename) {
        System.out.println("TF-IDF 導出");
        for (int i = 0; i < tf.list.size(); i++) { // TFの中の語の数だけくり返し
            Word word = tf.list.get(i).getWord();
            Integer count = tf.list.get(i).getCount();
            Double tfValue = tf.list.get(i).getTf();
            Double idfValue = 0.0;
            Double tfIdfValue = 0.0;
            for (int j = 0; j < df.list.size(); j++) { // DFの中の語の数だけくり返し
                DfCount dfCount = df.list.get(j);
                if (dfCount.getWord().equals(word)) {
                    idfValue = dfCount.getIdf();
                    tfIdfValue = tfValue * idfValue;
                    list.add(new tfIdfCount(word, count, tfValue, idfValue, tfIdfValue));
                    break;
                }
            }
        }
        list.sort(new tfIdfComparator());
        try {
            FileWriter fw = new FileWriter(outputFilename);
            System.out.println("出力ファイル: " + outputFilename);
            fw.write("#語\t出現回数\tTF\tIDF\tTF-IDF\t\n");
            for (tfIdfCount tfIdf : list) {
                fw.write(tfIdf.getWord().getGenkei() + "\t" + tfIdf.getCount() + "\t" +
                        tfIdf.getTf() + "\t" + tfIdf.getIdf() + "\t" + tfIdf.getTfidf() + "\n");
            }
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}