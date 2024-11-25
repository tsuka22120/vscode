public abstract class Car {
    protected int tire;
    protected int gas;
    protected int nenpi;

    // コンストラクタ
    Car() {
        System.out.println("車製造");
    }

    // コンストラクタのオーバーロード
    Car(int gas, int nenpi, int tire) {
        System.out.println("車作成中");
    }

    // タイヤの設定。異常な場合には補正する
    public void setTire(int tire){
        System.out.println("タイヤ:"   + tire);
        if (tire < 3) {
            System.out.println("タイヤの数が少なすぎます。4本に設定します。");
            this.tire = 4;
        } else {
            this.tire = tire;
        }
    }
    //ガスの設定を抽象メソッドとして定義
    public abstract void setGas();
    //燃費の設定を抽象メソッドとして定義
    public abstract void setNenpi();
    //タイヤ変数を取得
    public int getTire() {
        return tire;
    }
    //ガス変数を取得
    public int getGas() {
        return gas;
    }
    //燃費変数を取得
    public int getNenpi() {
        return nenpi;
    }
    //実行するたびに燃料を減らして車を動かし、残りの燃料を表示させる
    public void drive() {
        // setGas(getGas() - nenpi);
        gas -= nenpi;
        if(getGas() < 0) {
            System.out.println("ガス欠です！うごけません！");
            return;
        }
        System.out.println("ぶいーん  残燃料：" + getGas());
    }

}
