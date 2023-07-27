// Type violation in line 8
// 
// [8] Binary operator '+' expects both left and right to be the same.
// left expression on line 8 was of type 'int'
// right expression on line 8 was of type 'boolean'

class Test {
    private static int a = method(1 + true);
    public static int method(int b) {}
    public static void main(String[] args) {}
}
