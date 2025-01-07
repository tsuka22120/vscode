public class 哺乳類 extends 脊椎動物 {

	private int 毛の濃さ;

	哺乳類(int 生命力, int 毛の濃さ) {
		super(生命力);
		this.毛の濃さ = 毛の濃さ;
		System.out.println("毛の濃さ" + 毛の濃さ + "の哺乳類が生まれました");
	}

	public int 食事(int 生命力) {
		System.out.println("むしゃむしゃ");
		生命力++;
		System.out.println("生命力が" + 生命力 + "になりました");
		return 生命力;
	}

}
