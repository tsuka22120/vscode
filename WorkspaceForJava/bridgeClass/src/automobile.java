public class automobile extends Car{
    automobile(Movement move) {
        super(move);
    }

    public void back() {
        System.out.print("はふはふ");
        super.back();
    }
}
