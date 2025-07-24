public class main {
    public static void main(String[] args) throws Exception {
        System.out.println("-----人間-----");
        int 生命力;
        String name;
        name = "TSUKADA";
        生命力 = 10;
        人間 human = new 人間(生命力, 2, name);
        生命力 = human.食事(生命力);
        生命力 = human.考える(生命力, name);
        生命力 = human.動く(生命力);
        System.out.println("-----マグロ-----");
        生命力 = 10;
        マグロ maguro = new マグロ(生命力, 2, 1000);
        生命力 = maguro.泳ぐ(生命力);
        生命力 = maguro.鰓呼吸(生命力);
        System.out.println("-----カラス-----");
        生命力 = 10;
        カラス crow = new カラス(生命力, 2022, 50);
        生命力 = crow.飛行(生命力);
        生命力 = crow.ゴミあさり(生命力);
    }
}
