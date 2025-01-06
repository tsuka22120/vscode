public class 哺乳類 extends 脊椎動物 {

	private int 毛の濃さ;

	哺乳類(int 強さ, int 毛の濃さ) {
		super(強さ);
		this.毛の濃さ = 毛の濃さ;
		System.out.println("毛の濃さ" + 毛の濃さ + "の哺乳類が生まれました");
	}

	public void 食事() {
		System.out.println("むしゃむしゃ");
	}

}
