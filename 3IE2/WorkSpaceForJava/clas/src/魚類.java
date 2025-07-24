public class 魚類 extends 脊椎動物 {

	public 魚類(int 生命力, int うろこの硬さ) {
		super(生命力);
		this.うろこの硬さ = うろこの硬さ;
		System.out.println("うろこの硬さ" + うろこの硬さ + "の魚類が生まれました");
	}

	private int うろこの硬さ;

	public int 鰓呼吸(int 生命力) {
		System.out.println("こぉー");
		生命力--;
		System.out.println("生命力が" + 生命力 + "になりました");
		return 生命力;
	}

}
