public class Ambulance extends Car implements Siren {
  public Ambulance() {
    System.out.println("救急車製造");
  }
  //インターフェースを実装して、救急車のサイレンを鳴らす。
  public void callSiren() {
    System.out.println("ピーポーピーポー");
  }
  //燃料の設定を行う
  public void setGas() {
    this.gas = 120;
    System.out.println("搭載燃料：" + getGas());
  }
  //燃費の設定を行う。
  public void setNenpi() {
    this.nenpi = 5;
    System.out.println("燃費：" + getNenpi());
  }
}