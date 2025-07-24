public class PatrolCar extends Car implements Siren {
  public PatrolCar() {
    System.out.println("パトカー製造");
  }
  //インターフェースを実装して、パトカーのサイレンを鳴らす。
  public void callSiren() {
    System.out.println("うおーーーーん");
  }
  //燃料の設定を行う
  public void setGas() {
    this.gas = 12;
    System.out.println("搭載燃料：" + getGas());
  }
  //燃費の設定を行う。
  public void setNenpi() {
    this.nenpi = 5;
    System.out.println("燃費：" + getNenpi());
  }
}