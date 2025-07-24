public class マグロ extends 魚類 {

	public マグロ(int 生命力, int うろこの硬さ,int 重量) {
		super(生命力, うろこの硬さ);
		this.重量 = 重量;
		System.out.println("重量" + 重量 + "のマグロが生まれました");
	}

	private int 重量;

	public int 泳ぐ(int 生命力) {
		System.out.println("すぃー");
		生命力--;
		System.out.println("生命力が" + 生命力 + "になりました");
		return 生命力;
	}

}
