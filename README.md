# 🤖 Digi-Home: Smart Assistant & Memento Board

![Digi-Home Banner](https://img.shields.io/badge/Project-Digi--Home-blue?style=for-the-badge&logo=arduino)
![Status](https://img.shields.io/badge/Status-Active-success?style=for-the-badge)

> **A futuristic, interactive home automation assistant powered by Arduino and ESP32.**

---

## 📖 Overview

**Digi-Home** is an integrated ecosystem that combines animatronics, IoT home automation, and interactive robotics. It utilizes a powerful Master-Slave architecture to manage home appliances, provide visual feedback through an animated head, and perform physical tasks like dispensing items.

**(image={System Overview Diagram showing the connections between ESP32, Arduino Base, and Arduino Head})**

### 🚀 Key Features
*   **Animatronic Head**: Expressive 8x8 Matrix eyes and servo-controlled eyelids.
*   **Smart Home Hub**: Web-based control for high-voltage appliances (Lights, Fans).
*   **Automated Dispenser**: Dual servo mechanisms for dispensing tasks.
*   **Interactive Modes**: Includes Dance, Security Sweep, and Sleep modes.

---

## 🛠️ Bill of Materials (BOM)

Below is the comprehensive list of components required to build the **Memento Board By Adafruit** / Digi-Home system.

| Component | Qty | Purchase Link |
| :--- | :---: | :--- |
| **Memento Board By Adafruit** | 1 | [Buy Here](https://www.digikey.in/en/products/detail/adafruit-industries-llc/5420/24713460) |
| **LM2596S DC-DC Buck Converter**<br>(12V to 5V Power Supply) | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwi-s9zfpc-SAxXYi7kFHeRPAVMYACICCAEQCxoCdG0&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgk3q2Rp1X-Fxq70Ybz5UxVcnEgv6FfGYLRkfs30AvAJHRycZExgGnwaAqOnEALw_wcB&cid=CAAS9gHkaGxxsJj9F3XLQFR_wE38uP08j6LeN3dBplUuQMyo2Xga-kvpD95mSLkjBOZ6UY1ZQHwWThz0_E4nNr5_TS88mvfkT1ZzpLlO6y8r4yAggQMQ54PsrDLam0iNzHGnsNbujsYQocGlbVczGD34dUrDjw0_9IE4yQRFXX1CCJqDy8F6inWH60BVBLoy5J2aS-OJ_cJaQiIKwa476AnA1cBCLUOAUoE_8glOytPfr8QOW74H_KIQVSvcFwqDfu-g3n5WzHPtV_F4KXd4ZhK03sJKu4T6tsffXZyj0W0ZBUFq7JQ6I55LBFmULPYVXjdB_184JX9Y-yg&cce=2&category=acrcp_v1_32&sig=AOD64_1sUI7rkPTde1us6SPEPSeE4Bu1tQ&ctype=5&q=&nis=4&ved=2ahUKEwiWrNPfpc-SAxULbfUHHccANsQQ5bgDKAB6BAgPEAs&adurl=) |
| **LED 8X8 Matrix** | 2 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwiSjb64pM-SAxUjzDwCHUlXLDMYACICCAEQDxoCc2Y&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgmfL8adgrIf2403xE0zY5q7ujB0Z7k-ZC_qfSk-rquhepDIGOrnxmcaApTrEALw_wcB&cid=CAAS0wHkaEwPJ58JfBvA3JonpCz-IEEgrErm6A_Tf0xnThlZ1dvmvLVW7ZVH0745zrefxyrtlO33KW3LtFNEPHac9-xjNbO0f1cMwyMd81jQV153OW7y3P3cUHnTiYpN7GXArr79Bz7SlcCVdcNtePFS5_WIlFaoqf6EVWAW_SDZVmR-6ICM0tuExpjlWIqHvtvZNOtfrV3qC-1jWoK43iLylYpkBsEpfLEUZwXkiKUqTGRzjAkRF70YHaLOz1eIlJViyQiTgNzJV-cVwebhrBmVywKSKFNe&cce=2&category=acrcp_v1_32&sig=AOD64_19exCnIza_8z4KS-M052OAo3YMRA&ctype=5&q=&nis=4&ved=2ahUKEwjTnLW4pM-SAxWg4zgGHdctLggQ5bgDKAB6BAgGEBc&adurl=) |
| **MG995 Servo Motor**<br>(For Neck) | 2 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwiA_IbJpM-SAxWlqGYCHd16Mq8YACICCAEQDBoCc20&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgl2wCCCcUO1-TpGcpyFQvpYHgbEHKhzRqCi6t94odldZCJ8lLduMx8aApXdEALw_wcB&cid=CAAS0wHkaL9hbVCluVLg4jxYzZ1EdIMau7kXFVopDIX4vJgYzyXDAjUQ6K8x1Xs9FWcCN72Zj8UiBRiBWLb5qT3Vwt6GyNTgYaieTYj9HQYNNbtHgLcGIwWm2leW8XpVbp6CnlJyBAfmgA0477BZrroS_v7Aq1yGQSvIAMrXM2TaaxVrHOC8YBU3QZEdlzXpdTVN4SvJHIKvZQNgL96yHUzOpFQenP-D81Q_biqX_hD5bDCFJcRYPVTJMfLoCa7Q6n9FnM6ltPj61QkASjToqOulBCnmmiQo&cce=2&category=acrcp_v1_32&sig=AOD64_1yil5cQUQqXfDGbgJQJB7q5-W1bQ&ctype=5&q=&nis=4&ved=2ahUKEwiMq_7IpM-SAxXn3jgGHUfgF80Q5bgDKAB6BAgHEBM&adurl=) |
| **MG90S Servo Motor**<br>(For Antenna & Dispenser) | 4 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwiA_IbJpM-SAxWlqGYCHd16Mq8YACICCAEQEBoCc20&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgkKHMhf9VS0jlqx6y02sNmLjrgMajRkB7_1hNEVcT1jZZ6wCLAXeXEaAr3CEALw_wcB&cid=CAAS9gHkaIdgbcN34nLIjCsiYfGILNSvWX68CywEw6u8mH1kd2VrO1iBkK97u0Q9JU2liwVBymcDEBnsp9rdpY6NqQuKlvszjgE7pnheL1g-J4RT0sclrQIdwZXsDosb0e_pZGAvrcPBmHBVYIINZDBw_20f3l6_qOuoVpnnIiWe8vacN8qbl1Wtmy3KuCshMtUfn78046PsaQSKp9IYa8otoi2akApXfVBfnzX6eL3Wwe4audt6-8CX7dpFgZexQ3nlxlYVNy6AizRCtUxNYmQabT4WS2aAYmbFMsSFAW3uncewXpE_A218yejGCK_eLXZB0jiBDnRR7Ks&cce=2&category=acrcp_v1_32&sig=AOD64_0tLCgAJysRscgk8-5EtrjfXB0PIA&ctype=5&q=&nis=4&ved=2ahUKEwiMq_7IpM-SAxXn3jgGHUfgF80Q5bgDKAB6BAgHEA8&adurl=) |
| **Arduino Nano**<br>(To expand Pins) | 2 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwjD65m_ps-SAxWJuCkDHaHYNxQYACICCAEQCRoCdGI&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgmzkxnas7eT9BUOn2odhz3GDFBZbdpfahqy9N4LZ1oLT4chLITouyoaAkuzEALw_wcB&cid=CAAS9gHkaBnRJIAv4NSlU0BtLEjPG_x6zoCRh0bajtZEo9SFSkKqUik34ppMX3dqmKxx2xSUlfCMoNb1SXfdYH3jIIa8i1TP8qFidDPoB4LTv-xwiImw0rDXYc19VSSJxB5oUBMlYLzpRVvHQm3DHK4dZFCYxx756UBiMzSf5f1n54BYhXS5dMsWw7iBpiUglVuRrfacApIvhrjaq5Avdvi0pUMqDdmy_RiGQLY3bzLn4w-UJGnBPRYFy0svuZi90iR8Iy8ZPxhIzT5kTbV3--tG9QaI4gkXY2vwTjjSeNpuHW2Bi9nLb-6nouo73zojJ8bIeNIINpJpu3g&cce=2&category=acrcp_v1_32&sig=AOD64_0VA_2AzJJ6oCFxKcN8ybXdwZVQog&ctype=5&q=&nis=4&ved=2ahUKEwici5K_ps-SAxXpc_UHHctrMzAQ5bgDKAB6BAgJEB8&adurl=) |
| **24 AWG Wires Bundle**<br>(5 meter) | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwiKkq7fps-SAxXwaw8CHRw2HZIYACICCAEQEhoCdGI&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgmRnwJpgZr_g1VrEluhgyT5rwMgwZ2rhC8ZM005mhyeyaDa1DPECgYaAibZEALw_wcB&cid=CAAS9gHkaJi4wzTLga9YJ2cTWBY7wuIk3GSE96zb2X_4oGE9kmmPErZD3I4MvoJT0xN8ZzVHOOzG5hPBExC87HaoRn1qFDh7hwEYVbnLRKmr4pU7i2Wfd8za53ukS0FcLu2B9T5yXj5owfgZyEI2k8CvRSUtYUEQ3o7SGVssaVCH_qn3B-QrCuamHvSRY1r7Hva4mwZcXrXM0Y_Q_5ko3kXPyqynu9vUL8j_TznhTtnxLItopQWdU0wjKNiGTd2Ekj8suJ1PsmvL1Unl7cdZ2h1iN74W7c6yd7QNo95HaN4CNGgNB4WFgnlWOEKB-dTOzkhAvcb6eSQe8UE&cce=2&category=acrcp_v1_32&sig=AOD64_26lMbOcxxnI000zgAWy8gQtqAOeg&ctype=5&q=&nis=4&ved=2ahUKEwintabfps-SAxU1iK8BHVtfJ3YQ5bgDKAB6BAgLEBc&adurl=) |
| **eSun PLA+ 1.75mm**<br>(Color of choice) | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwjf2bKVp8-SAxXBLXsHHQMuPHoYACICCAEQDBoCdG0&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOglmmLtjJmZciyNl89-lBIen8V-ZzCnBAexf2orb1MWalVd9HY-sceYaAr2gEALw_wcB&cid=CAAS9gHkaEz1cKUcR9JCx2CbJD3LpH3i8s2cJMh2zU531PbZlYzIXlOZt-yXwIfdJan0rs0N3_vpqM8a48qIAWjba-k_GXeDGgUGwOlProaM027I8Oo3H5GfCYYS5LKK_fXzih8AQLDdUHDF93uFMxzpTgrw-qQ0msco4OcNMik7Yhb5jUW0w5wTOqmGici5m-NXTxneAio5WdUHEq3S2utfgv651cWJpOFyS0oRalpxcaz6TTHX9wi8IDpActLuIPjMMSnLxipecP-_IwIx3x9uEZ3dwMyfVlQIWwA9wzNy7cCWE5X66KTJaRwZLgkOK0W7d2Lin6tqHrg&cce=2&category=acrcp_v1_32&sig=AOD64_2K-FkpZ8EpTG427DAfOHZgNnd2rw&ctype=5&q=&nis=4&ved=2ahUKEwjX6amVp8-SAxV1iK8BHY7lOgsQ5bgDKAB6BAgMEAs&adurl=) |
| **Soldering Iron Kit** | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwjy0pm-p8-SAxX2JXsHHXHoI98YACICCAEQDhoCdG0&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOglEP88SlmA600q5_XQnvQkF_GeGnwhTYXV-mesPNbQe4H9QdJA1wIcaAlAbEALw_wcB&cid=CAAS9gHkaD9nNaMGrA9Esmqo7YmGaPeIk82s89ajFJYh4y18-ZNWqw7JqxNoy5AfVQoPpVbwjArBCfmVDR0R80yRjpD8Q24aXuu8GpVd_EZcBk672f_iWhDYJqirJ1DGYMCv80zHICLlEg9fq4IREMUgQKcwgTM8YHltNm32qbHNrdtpXXuITxE0Dt6U4RnxD51zXi61zUS64ZqYYkuNV-OpVwFC21ZJ3Ve--QOy8jb6r9bCBbmbzD7UfgwRtR9NUbjBED5lJqDLOE49vxjXfCQpovGFpP_I0HP-mOXhojAKs56wNSo9cF1Px6hz7DVkb9bjZYmAcHOviwU&cce=2&category=acrcp_v1_32&sig=AOD64_0DI5KFb9102hNmpZNUV0HYWI5b5g&ctype=5&q=&nis=4&ved=2ahUKEwjtlZG-p8-SAxXpcfUHHZnhAnIQ5bgDKAB6BAgGEAs&adurl=) |
| **Glue Gun** | 1 | [Buy Here](https://www.meesho.com/glue-guns/pl/997?srsltid=AfmBOor-x8Y_ux-g0ucn7r0g1IZt1v4XrUss-9I_4eg-g9kcGDKD0NQX) |
| **ESP32 Wroom DA** | 1 | [Buy Here](https://robu.in/product/esp-wroom-32-esp32-wifi-bt-ble-mcu-module/) |
| **4 Channel Relay** (5V) | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwizhqSXwM-SAxU8yxYFHZLvLSAYACICCAEQBBoCdGw&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgn__FjLbJv8w-fDeQr9gRb-lIsL7-xEagmBH36pWsqnSK_hBafLYsEaAutAEALw_wcB&cid=CAAS0wHkaM2qlPJEKUW7MhNhsyzAhffEVkZtOrAVwMbb47Y6KQLOnZKPrYdpPEsI2nEj58xULg8UrSYsWYKepXj4TDiTcYiQc9qIdbGgCPCqVVtizyF2YhCJa7aFcLs7p5xFHlGxhdHXeniOdjZcLWuoEMAc0xBbUmIvRpM-yOdBi_v_xPFPQhNH50G4gMuPCkhL4WX8E3rfSZDY2FvNKuPirLKfURUj6XWMUB3Ss4CisnkTikR8z-dPAqgWEj-V8bR65FJWrA4aw3oSZaEbkOuC_7486WPS&cce=2&category=acrcp_v1_32&sig=AOD64_21dEYCZANBEndh4eV1PdneoSS99g&ctype=5&q=&nis=4&ved=2ahUKEwiYz5yXwM-SAxVa1jQHHShyKSsQ5bgDKAB6BAgKEA8&adurl=) |
| **Li-Ion Battery Pack** (12V) | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwjnqKGaws-SAxWl9RYFHZC9H3MYACICCAEQERoCdGw&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgnpnegFMGi_7gzyuEL8FJwIEjHA2xbl6U5hJ7olnx9G_4ks0nEsAi4aAnHxEALw_wcB&cid=CAAS9gHkaCXwQfSMBGvNICHGlJaTHpmh5nJV7vLwRZjdFyVmrYWHdz5mh17BbxYucNWOYTV_OiDAW1EHsjktOGsI88SIovN-012RIWMvVovoDmP0e-O3T77V_wU5yetf7v0_oQNJbThnvNqs8IdklqEKgIqY6YEd-QTYnayw9QHFXjSIetTBLaJx6TiD9-mBvPETojdC4dm88RrUENT02x00QQvMX4pRwdGJ55EC4r7X4g2tuYrwy6-p4nCJDYcjFpk9UZNgdr6LRUU4WddAR-K8nWO2nL35kYkJZOvLqKAAq2Pm3EzlToX9XkHGiuoJuA8lqQy2_N6gIvA&cce=2&category=acrcp_v1_32&sig=AOD64_35vR8sJ3yKJXrUWyt12X8SoeOAAQ&ctype=5&q=&nis=4&ved=2ahUKEwiQqZmaws-SAxV2rVYBHQXKDAsQ5bgDKAB6BAgJECQ&adurl=) |
| **Wall Adapter** (5V 4A) | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwjdqqzkws-SAxXjhrkFHSFpMX4YACICCAEQBRoCdG0&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgnxsTD2MxSGVaHq1-YjUUxpHclJyjPB3gMr-6fP2NU9BSG6qZcqGRoaAuqVEALw_wcB&cid=CAAS9gHkaIyFgBlG9L1F24j40iIaD9ny7mC-4I_POyCWim66mc8P1BYQKJGsn73HGb_W3p7kUwY8ei6ZtsVoA2Isd1eGiLLgPtI7ydJm95YhvM735Dqhhsp67xVoX73Y6QM0ejIkpiSegGC8nwVAr-QBBvpIdT7Yq9ZNNx3C8JUAmaGBeBOhcbV4MMc87znliU3MR_wlX7Qy01Vlz9KbkMF3h-YTc8Kes7C8siez2xTTCKn6pzox_vaql2Sfydw3Oz84EhmsHKWVSb4PpCBICcx5q35dUoZxHhdtXhm_1iuSk71bVJGiDZVLFu2wRCCPqvpFkvfuJSVJFx0&cce=2&category=acrcp_v1_32&sig=AOD64_3Ktyg4BCTMooL7cjwtEnqvpNVU9w&ctype=5&q=&nis=4&ved=2ahUKEwik06Tkws-SAxWIqVYBHf3VBHAQ5bgDKAB6BAgFEBA&adurl=) |
| **Screw Driver Set** | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwjby9Wjw8-SAxUDmLkFHYDNLU4YACICCAEQBRoCdG0&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOglp8R36W2eyosTGg918C-qDzsBbZ72r9_jM63IDiJM-WsRxULd7_rcaAr8XEALw_wcB&cid=CAAS9gHkaKtnzf8x9TJMX3Qt4sceCivcRyjhqwON41lRwQLzTXW-josz0_doaehhlecfQlm5B5Gbnd843e-7FVjGI4CDzGyrk4JJEUoS1FrNPw4W6YdSSo82cTyjOIIOHDvlP5E997h4NRpIDpj4BcRVhQeGsh_nzTGDSwM5X2FQJ33ZdfQK3XLNkYxg9VdtToFae82hWi2h3htmef4Pmxc7u6FH-8A-sRYcdraItOyH2aaScELwNc7VSGwljv31aIITsf4RqSRcfjOiGjg4IIbRreJ1XzBf7Ivet1Qpu9A0o8cj3taNErFOB_WLhHGg1uv2NWOdBvOD-BI&cce=2&category=acrcp_v1_32&sig=AOD64_2IV3b3rbL4p2gLKxzZ6xiMl0Osog&ctype=5&q=&nis=4&ved=2ahUKEwjrls6jw8-SAxUnr1YBHdBsJhoQ5bgDKAB6BAgFEA8&adurl=) |
| **Wire Cutter** | 1 | [Buy Here](https://kitsguru.com/products/economy-precision-flush-cutter-pcb-wire-nipper-cutting-tool?variant=48591803941116&country=IN&currency=INR&utm_medium=product_sync&utm_source=google&utm_content=sag_organic&utm_campaign=sag_organic&srsltid=AfmBOooVkUzRcXpzuAR8L-lYS0JHtCNQreehoGTBw4gAmpKR5jyaeGkyfRw) |
| **DT830D Multimeter** | 1 | [Buy Here](https://robu.in/product/digital-multimeter-small-yellow-color-lcd-ac-dc-measuring-voltage-current/) |
| **M4x8mm Screws** | 8 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwiFl7_oxdKSAxWWpmYCHT5uKk4YACICCAEQFxoCc20&co=1&ase=2&gclid=Cj0KCQiA7rDMBhCjARIsAGDBuEAlQGzAZw0qdem7-60RNQTOT9dNPo6ykoIa4cxmq4PgOs9AnO_VPZsaApwIEALw_wcB&cid=CAAS0wHkaDrtpdPDzT8eAJFteGg9GsbXG6jPiPOHJ-KTtoZaOPOs_8sBrSd1u6q8nRABgkoGZIjqerokGcEXLuWtTRwS8_RlfHFiwiSp9cpPbfJDTV1AP025ihbMH0fil_tkndXsgKOXgEI9urFq8f_jCqZ6w3d2vdMmKCu09Juvdmuig3vcRH8iKE2tn41WeLsnkxwYT6cfz2LSHIwzpGTtyD8Wp959QHr3ICj7kXq2nIfW-GTDgYWx3lM_hM-gh0CFRACVbjeoTngKsZuwv5qZQ0KS2iGi&cce=2&category=acrcp_v1_32&sig=AOD64_1GtmLVPU2Hxh4FOlbq2U59gB3gYg&ctype=5&q=&nis=4&ved=2ahUKEwjPyLfoxdKSAxX-UGwGHSrjLBcQ5bgDKAB6BAgKECA&adurl=) |

---

## ⚡ Hardware Architecture & Wiring

### 1. Base Controller (Body)
**Role**: Controls the robot's neck movements and dispensing mechanisms.  
**File**: `Base_trigger.ino` (or `Slave_Boards/0x08.ino`)  
**Pins**:
- **Neck Roll**: `D3`
- **Neck Yaw**: `D5`
- **Dispenser 1**: `D6`
- **Dispenser 2**: `D9`

**(image={Wiring diagram for Base Controller showing Servos connected to D3, D5, D6, D9})**

### 2. Head Controller (Face)
**Role**: Manages the robot's facial expressions and eyelid movements (8x8 Matrix).  
**File**: `head_arduino_0x09.ino` (or `Slave_Boards/0x09.ino`)  
**Pins**:
- **LED Matrix CS**: `D10`
- **Right Eyelid Servo**: `D3`
- **Left Eyelid Servo**: `D6`

**(image={Wiring diagram for Head Controller showing LED Matrix connection and Eyelid Servos})**

### 3. Appliance Controller (IoT)
**Role**: Controls high-voltage appliances via relays and provides a Web Interface.  
**File**: `esp32_relay_module.ino`  
**Pins**:
- **Light Relay**: `GPIO 26`
- **Fan Relay**: `GPIO 27`

**(image={Wiring diagram for ESP32 Relay Module connected to Light and Fan})**

---

## ⚙️ Usage

### Web Control
Connect to the ESP32's IP address to access the control panel:
- **Toggle Light**: `http://<ESP_IP>/light_on`
- **Toggle Fan**: `http://<ESP_IP>/fan_on`

**(image={Screenshot of the ESP32 Web Control Interface})**

### I2C Commands
The System uses a Master-Slave I2C bus.
- **Base (0x08)**: `"dance"`, `"secure"`, `"slot_08"`, `"medicine_slot_09"`
- **Head (0x09)**: `"exp1"` (Sad), `"exp2"` (Happy), `"secure"`, `"sleep"`

**(image={Photo of the robot head displaying different expressions})**

---

## 🏗️ Installation

1.  **Clone the Repo**:
    ```bash
    git clone https://github.com/vikas-meu/digi-home-hw.git
    ```
2.  **Upload Firmware**:
    - **Base**: Upload `Base_trigger.ino` to Arduino @ `0x08`.
    - **Head**: Upload `head_arduino_0x09.ino` to Arduino @ `0x09`.
    - **ESP32**: Update WiFi credentials in `esp32_relay_module.ino` and upload.

**(image={Screenshot of Arduino IDE showing the correct Board and Port selection})**

---

## 🐛 Troubleshooting

*   **Servos Jittering**: Ensure you are using an **external 5V 4A power supply**. USB power is not enough!
*   **Matrix Garbage**: Check `HARDWARE_TYPE` in `head_arduino` (Try `FC16_HW` or `GENERIC_HW`).
*   **I2C Errors**: Ensure **Common Ground** is connected between all devices.

---

> **Memento Board By Adafruit Project**

