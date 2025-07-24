public class 人間 extends 哺乳類 {

	public 人間(int 生命力, int 毛の濃さ, String 名前) {
		super(生命力, 毛の濃さ);
		System.out.println("生命力" + 生命力 + "の" + 名前 + "が生まれました");
	}
	private String 名前;

	public int 考える(int 生命力, String 名前) {
		System.out.println(名前 +"は考えた");
		生命力--;
		System.out.println("生命力が" + 生命力 + "になりました");
		return 生命力;
	}

}
