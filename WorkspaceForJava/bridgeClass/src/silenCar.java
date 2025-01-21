public class silenCar {
    private Movement move;

    silenCar(Movement move) {
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

    public void call(){
        move.call();
    }
}
