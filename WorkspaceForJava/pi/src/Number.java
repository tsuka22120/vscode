public class Number {
    private List<Integer> digits;
    private boolean sign; // true for positive, false for negative
    private int RADIX = 10; // base 10 for decimal numbers

    public Number(int number){
        digits = new ArrayList<Integer>();
        if(number < 0) {
            sign = false;
            number = -number;
        } else {
            sign = true;
        }
        while(number > 0) {
            digits.add(number % RADIX);
            number /= RADIX;
        }
    }
}