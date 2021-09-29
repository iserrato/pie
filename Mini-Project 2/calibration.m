in = [7 7.5 8 8.5 9 9.5 10 10.5 11 11.5 12 12.5 13  13.5 14 14.5 15 15.5 16 16.5 17 17.5 18 18.5 19 19.5 20 20.5 21 21.5 22 22.5 23 23.5 24 24.5 25 25.5 26 26.5 27 ];
val = [561 548 534 520 505 488 472 457 444 430 419 405 394 378 367 349 338 325 316 306 301 286 282 275 268 265 252 245 241 237 230 226 222 218 214 212 208 204 200 196 196];

last_six_in = [27.5 28 28.5 29 29.5 30];
last_six_vals = [ 188 188 185 184 180 177];

total_in = [in last_six_in];
total_val = [val last_six_vals];

total_cm = total_in .* 2.54;
cm = in .* 2.54;

test_cms = [20 25 30];
test_ans = [540 484 422];

f = fit(cm', val','exp1');

plot(f, cm, val, '.');
axis([15 75 150 600])
grid('on');
title('Calibration Data with Fitted Line')
legend('Experiemental Readings', 'Fitted Curve')
xlabel('Distance (cm)')
ylabel('IR Sensor Value')

