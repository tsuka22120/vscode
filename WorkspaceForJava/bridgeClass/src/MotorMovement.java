public class MotorMovement extends Movement {
    @Override
    public void forward() {
        System.out.println("シュウィーン「前進します」");
    }

    @Override
    public void back() {
        System.out.println("シュッ「バックします」");
    }

    @Override
    public void turn(Boolean side) {
        if (side) {
            System.out.println("シュッ「右に曲がります」");
        } else {
            System.out.println("シュッ「左に曲がります」");
        }
    }

    public void call(){
    }
}