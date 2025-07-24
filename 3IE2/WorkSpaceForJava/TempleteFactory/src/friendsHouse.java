public class friendsHouse extends goingOut {
    friendsHouse() {
        System.out.println("===友達の家に行く===");
    }

    @Override
    public void goTo() {
        System.out.println("家を出るお");
        System.out.println("歩くお");
        System.out.println("友達の家に着いたお");
    }

    @Override
    public void toDo() {
        System.out.println("ゲームをするお");
        System.out.println("お菓子を食べるお");
    }

    @Override
    public void goBack() {
        System.out.println("友達の家を出るお");
        System.out.println("歩くお");
        System.out.println("家に着いたお");
    }
}