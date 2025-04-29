float integralSinX(float a, float b) {
    return simpsonRule(a, b, NUM_PARTS);
}

float simpsonRule(float a, float b, int numParts) {
    float h = (b - a) / numParts;
    float ans = 0.0;
    ans = sin(a) + sin(b);
    for (int i = 1; i <= numParts - 1; i++) {
        if(i % 2 == 0) {
            ans += 2 * sin(a + i * h);
        } else {
            ans += 4 * sin(a + i * h);
        }
    }
    ans *= h / 3;
    return ans;
}