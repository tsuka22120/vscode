public class Bus extends Car {
    Bus(Movement move) {
        super(move);
    }

    public void back() {
        System.out.print("「後ろに下がります．ご注意ください．」");
        super.back();
    }
}