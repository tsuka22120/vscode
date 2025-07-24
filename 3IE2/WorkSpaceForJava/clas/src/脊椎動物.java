public class 脊椎動物 extends いきもの {

	public 脊椎動物(int 生命力) {
		super(生命力);
		System.out.println("生命力" + 生命力 + "の脊椎動物が生まれました");
	}

	public int 動く(int 生命力) {
		System.out.println("ぐいぐい");
		生命力--;
		System.out.println("生命力が" + 生命力 + "になりました");
		return 生命力;
	}

}
