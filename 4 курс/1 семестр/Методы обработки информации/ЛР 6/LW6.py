from scipy.stats import ttest_ind_from_stats
import numpy as np

alpha = 0.01
t_statistic, p_value = ttest_ind_from_stats(mean1=5.51, std1=np.sqrt(0.79), nobs1=123,
                     mean2=6.95, std2=np.sqrt(1.09), nobs2=123)
print("t-статистика:", t_statistic)
print("P-значение:", p_value)

if p_value < alpha:
    print("Нулевая гипотеза отклонена. Средняя оценка валидности теста для группы с отрицательной обратной связью ниже, чем для группы с положительной обратной связью")
else:
    print("Нулевая гипотеза не отклонена. Средние оценки валидности теста для группы с отрицательной обратной связью и группы с положительной обратной связью равны")
