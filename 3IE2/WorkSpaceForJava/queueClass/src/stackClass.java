class Stack {
    static int defaultSize = 5;
    static int stack[] = new int[defaultSize];
    static int volume = 0;

    // データ追加関数
    static void push(int number) {
        if(stack.length > volume){
            stack[volume] = number;
            volume++;
            System.out.printf("%d inserted\n",number);
        } else {
            System.out.printf("OverFlow\n"); 
        }
    }

    // データ取得関数
    static int pop(){
        int returnValue = 0;
        if(volume > 0){
            returnValue = stack[volume-1];
            volume--;
        } else {
            System.out.printf("UnderFlow\n");
            returnValue = -1;
        }
        return returnValue;
    }

    //状態表示関数
    static void printStack(){
        System.out.printf("|");
        for(int i = 0;i < stack.length;i++){
            System.out.printf("%d|",stack[i]);
        }
        System.out.println();
    }
    public static void main(String[] args){
        push(10);printStack();
        push(20);printStack();
        push(30);printStack();
        push(40);printStack();
        push(50);printStack();
        push(60);printStack();
        System.out.printf("%d poped\n",pop());
        printStack();
        System.out.printf("%d poped\n",pop());
        printStack();
        System.out.printf("%d poped\n",pop());
        printStack();
        System.out.printf("%d poped\n",pop());
        printStack();
        System.out.printf("%d poped\n",pop());
        printStack();
        System.out.printf("%d poped\n",pop());
        printStack();
    }
}