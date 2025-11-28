import matplotlib.pyplot as plt
import numpy as np

# Dados baseados na análise experimental do relatório
sizes = [50*50, 100*100, 200*200]  # n = w×h pixels
size_labels = ['50×50\n(2.5K)', '100×100\n(10K)', '200×200\n(40K)']

# Tempos relativos (normalizados para 100×100 = 1.0)
# Assumindo complexidade linear O(n)
best_case = [0.0001, 0.0002, 0.0004]  # Ω(1) - quase constante
average_case = [0.293, 1.0, 4.0]      # ~58.6% do pior caso
worst_case = [0.5, 1.7, 6.8]          # Θ(n) - linear

plt.figure(figsize=(10, 6))

plt.plot(size_labels, best_case, 'g-o', linewidth=2, markersize=8, label='Melhor Caso (Ω(1))')
plt.plot(size_labels, average_case, 'b-s', linewidth=2, markersize=8, label='Caso Médio (O(n))')
plt.plot(size_labels, worst_case, 'r-^', linewidth=2, markersize=8, label='Pior Caso (Θ(n))')

plt.xlabel('Dimensão da Imagem (pixels)', fontsize=12)
plt.ylabel('Tempo de Execução (unidades relativas)', fontsize=12)
plt.grid(True, alpha=0.3)
plt.legend()

# Anotações
plt.annotate('Terminação antecipada\n(primeiro pixel diferente)', 
             xy=(0, best_case[0]), xytext=(0.5, 0.1),
             arrowprops=dict(arrowstyle='->', color='gray'),
             fontsize=9)

plt.annotate('Crescimento linear\ncom número de pixels', 
             xy=(2, worst_case[2]), xytext=(1.5, 5),
             arrowprops=dict(arrowstyle='->', color='gray'),
             fontsize=9)

plt.tight_layout()
plt.show()