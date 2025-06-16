package nlp;

class WordCount {
    private Word word;
    private Integer count;

    public WordCount(Word word, Integer count) {
        this.word = word;
        this.count = count;
    }

    public Word getWord() {
        return word;
    }

    public void setWord(Word word) {
        this.word = word;
    }

    public Integer getCount() {
        return count;
    }

    public void setCount(Integer count) {
        this.count = count;
    }
}

class TfCount extends WordCount {
    private Double tf;

    public TfCount(Word word, Integer count) {
        super(word, count);
    }

    public TfCount(Word word, Integer count, Double tf) {
        super(word, count);
        this.tf = tf;
    }

    public Double getTf() {
        return tf;
    }

    public void setTf(Double tf) {
        this.tf = tf;
    }
}

class DfCount extends WordCount {
    private Double idf;
    private Integer df;

    public DfCount(Word word, Integer count, Double idf, Integer df) {
        super(word, count);
        this.idf = idf;
        this.df = df;
    }

    public Double getIdf() {
        return idf;
    }

    public void setIdf(Double idf) {
        this.idf = idf;
    }

    public Integer getDf() {
        return df;
    }

    public void setDf(Integer df) {
        this.df = df;
    }
}

class tfIdfCount extends WordCount {
    private Double tfidf;
    private Double tf;
    private Double idf;

    public tfIdfCount(Word word, Integer count, Double tf, Double idf, Double tfidf) {
        super(word, count);
        this.tfidf = tfidf;
        this.tf = tf;
        this.idf = idf;

    }

    public Double getTfidf() {
        return tfidf;
    }

    public void setTfidf(Double tfidf) {
        this.tfidf = tfidf;
    }

    public Double getTf() {
        return tf;
    }

    public void setTf(Double tf) {
        this.tf = tf;
    }

    public Double getIdf() {
        return idf;
    }

    public void setIdf(Double idf) {
        this.idf = idf;
    }
}