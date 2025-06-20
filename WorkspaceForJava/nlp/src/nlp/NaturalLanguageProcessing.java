//javac -d bin src/nlp/*.java
//java -cp bin nlp.NaturalLanguageProcessing
package nlp;


public class NaturalLanguageProcessing {
    static public void main(String args[]) {
        System.out.println("TF 導出");
        TermFrequency[] tf = new TermFrequency[100];
        for (int i = 1; i <= 100; i++) {
            tf[i - 1] = new TermFrequency();
            String inputFileName = "./data/" + String.format("%03d", i) + ".txt";
            String outputFileName = "./out/" + String.format("%03d", i) + "tf.txt";
            System.out.println(inputFileName);
            System.out.println(outputFileName);
            tf[i - 1].tf(inputFileName, outputFileName);
        }
        DocumentFrequency df = new DocumentFrequency(tf);
        df.df("./out/df.txt");
        System.out.println("tf-idf 導出");
        for(int i = 1;i <= 100; i++) {
            String outputFileName = "./out/" + String.format("%03d", i) + "tfidf.txt";
            termFrequency_inverseDocumentFrequency tfIdf = new termFrequency_inverseDocumentFrequency(tf[i - 1], df);
            tfIdf.tfIdf(outputFileName);
        }
        System.out.println("完了しました");
    }
}
