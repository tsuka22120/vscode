public class HydrogenMovement extends Movement {
    public void forward() {
        System.out.println("プシュ「前進します」");
    }

    public void back() {
        System.out.println("ヴーん「バックします」");
    }

    public void turn(Boolean side) {
        if (side) {
            System.out.println("シュッ「右に曲がります」");
        } else {
            System.out.println("シュッ「左に曲がります」");
        }
    }

    public void call() {
    }
}