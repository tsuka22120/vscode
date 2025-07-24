public class school extends goingOut {
    school() {
        System.out.println("===学校に行く===");
    }

    @Override
    public void goTo() {
        System.out.println("家を出るお");
        System.out.println("電車に乗るお");
        System.out.println("学校に着いたお");
    }

    @Override
    public void toDo() {
        System.out.println("授業を受けるお");
        System.out.println("部活をするお");
    }

    @Override
    public void goBack() {
        System.out.println("学校を出るお");
        System.out.println("電車に乗るお");
        System.out.println("家に着いたお");
    }
}