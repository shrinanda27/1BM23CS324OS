#include <stdio.h>

int main() {
	int n, m, i, j, k;
	printf("Enter the number of processes and resources : ");
	scanf("%d %d", &n, &m);

	int allo[n][m], request[n][m], avail[m];
	printf("Enter the allo matrix:\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			scanf("%d", &allo[i][j]);

	printf("Enter the request matrix:\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			scanf("%d", &request[i][j]);

	printf("Enter the avail resources:\n");
	for (i = 0; i < m; i++)
		scanf("%d", &avail[i]);

	int finished[n], deadlocked[n], deadlock_count = 0;
	for (i = 0; i < n; i++) finished[i] = 0;

	while (1) {
		int found = 0;
		for (i = 0; i < n; i++) {
			if (!finished[i]) {
				for (j = 0; j < m; j++)
					if (request[i][j] > avail[j]) break;
				if (j == m) {
					for (k = 0; k < m; k++)
						avail[k] += allo[i][k];
					finished[i] = 1;
					found = 1;
				}
			}
		}
		if (!found) break;
	}

	for (i = 0; i < n; i++) {
		if (!finished[i]) {
			deadlocked[deadlock_count++] = i;
		}
	}

	if (deadlock_count == 0)
		printf("No deadlock detected.\n");
	else {
		printf("Deadlock detected. Deadlocked processes: ");
		for (i = 0; i < deadlock_count; i++)
			printf("%d ", deadlocked[i]);
		printf("\n");
	}
	return 0;
}
