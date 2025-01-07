public class 鳥類 extends 脊椎動物 {

	public 鳥類(int 生命力, int 巣の場所) {
		super(生命力);
		this.巣の場所 = 巣の場所;
		System.out.println("巣の場所" + 巣の場所 + "の鳥が生まれました");
	}
	private int 巣の場所;

	public int 飛行(int 生命力) {
		System.out.println("ひゅー");
		生命力--;
		System.out.println("生命力が" + 生命力 + "になりました");
		return 生命力;
	}

}
