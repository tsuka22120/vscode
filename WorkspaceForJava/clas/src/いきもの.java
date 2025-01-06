public abstract class いきもの {

	private int 生命力;

	public void 生きる() {
		生命力--;
		System.out.println("どくどく");
		System.out.println("生命力が" + 生命力 + "になりました");
	}
}
