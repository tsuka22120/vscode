public abstract class いきもの {

	private int 生命力;

	public いきもの(int 生命力) {
		this.生命力 = 生命力;
		System.out.println("生命力" + this.生命力 + "の生き物が生まれました");
	}
	public void 生きる() {
		生命力--;
		System.out.println("どくどく(生きている！)");
		System.out.println("生命力が" + 生命力 + "になりました");
	}
}
