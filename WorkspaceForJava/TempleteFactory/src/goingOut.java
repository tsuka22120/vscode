abstract public class goingOut {
    abstract public void goTo();

    abstract public void toDo();

    abstract public void goBack();

    // これがテンプレートメソッド
    public void working() {
        goTo();
        toDo();
        goBack();
    }
}