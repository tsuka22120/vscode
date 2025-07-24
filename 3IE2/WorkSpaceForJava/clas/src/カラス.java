public class カラス extends 鳥類 {

	public カラス(int 生命力, int 巣の場所, int 賢さ) {
		super(生命力, 巣の場所);
		this.賢さ = 賢さ;
		System.out.println("賢さ" + 賢さ + "のカラスが生まれました");
	}

	private int 賢さ;

	public int ゴミあさり(int 生命力) {
		System.out.println("ガサゴソ");
		生命力--;
		System.out.println("生命力が" + 生命力 + "になりました");
		return 生命力;
	}

}
