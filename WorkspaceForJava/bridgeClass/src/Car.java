public class Car {
    private Movement move;

    Car(Movement move) {
        this.move = move;
    }

    public void forward() {
        move.forward();
    }

    public void back() {
        move.back();
    }

    public void turn(Boolean side) {
        move.turn(side);
    }
}