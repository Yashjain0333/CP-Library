int GCD(int A, int B) {
	if (B == 0)
		return A;
	else
		return GCD(B, A % B);
}