# 🤖 Digi-Home: Smart Assistant & Memento Board

![Digi-Home Banner](https://img.shields.io/badge/Project-Digi--Home-blue?style=for-the-badge&logo=arduino)
![Status](https://img.shields.io/badge/Status-Active-success?style=for-the-badge)

> **A futuristic, interactive home automation assistant powered by Arduino and ESP32.**  
> *Transform your space with animatronic expressions, IoT control, and automated dispensing.*

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

| Component | Qty | Purchase Link |
| :--- | :---: | :--- |
| **Memento Board By Adafruit** | 1 | [Buy Here](https://www.digikey.in/en/products/detail/adafruit-industries-llc/5420/24713460) |
| **LM2596S DC-DC Buck Converter Power Supply (12v to 5 v)** | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwi-s9zfpc-SAxXYi7kFHeRPAVMYACICCAEQCxoCdG0&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgk3q2Rp1X-Fxq70Ybz5UxVcnEgv6FfGYLRkfs30AvAJHRycZExgGnwaAqOnEALw_wcB&cid=CAAS9gHkaGxxsJj9F3XLQFR_wE38uP08j6LeN3dBplUuQMyo2Xga-kvpD95mSLkjBOZ6UY1ZQHwWThz0_E4nNr5_TS88mvfkT1ZzpLlO6y8r4yAggQMQ54PsrDLam0iNzHGnsNbujsYQocGlbVczGD34dUrDjw0_9IE4yQRFXX1CCJqDy8F6inWH60BVBLoy5J2aS-OJ_cJaQiIKwa476AnA1cBCLUOAUoE_8glOytPfr8QOW74H_KIQVSvcFwqDfu-g3n5WzHPtV_F4KXd4ZhK03sJKu4T6tsffXZyj0W0ZBUFq7JQ6I55LBFmULPYVXjdB_184JX9Y-yg&cce=2&category=acrcp_v1_32&sig=AOD64_1sUI7rkPTde1us6SPEPSeE4Bu1tQ&ctype=5&q=&nis=4&ved=2ahUKEwiWrNPfpc-SAxULbfUHHccANsQQ5bgDKAB6BAgPEAs&adurl=) |
| **LED 8X8 Matrix** | 2 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwiSjb64pM-SAxUjzDwCHUlXLDMYACICCAEQDxoCc2Y&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgmfL8adgrIf2403xE0zY5q7ujB0Z7k-ZC_qfSk-rquhepDIGOrnxmcaApTrEALw_wcB&cid=CAAS0wHkaEwPJ58JfBvA3JonpCz-IEEgrErm6A_Tf0xnThlZ1dvmvLVW7ZVH0745zrefxyrtlO33KW3LtFNEPHac9-xjNbO0f1cMwyMd81jQV153OW7y3P3cUHnTiYpN7GXArr79Bz7SlcCVdcNtePFS5_WIlFaoqf6EVWAW_SDZVmR-6ICM0tuExpjlWIqHvtvZNOtfrV3qC-1jWoK43iLylYpkBsEpfLEUZwXkiKUqTGRzjAkRF70YHaLOz1eIlJViyQiTgNzJV-cVwebhrBmVywKSKFNe&cce=2&category=acrcp_v1_32&sig=AOD64_19exCnIza_8z4KS-M052OAo3YMRA&ctype=5&q=&nis=4&ved=2ahUKEwjTnLW4pM-SAxWg4zgGHdctLggQ5bgDKAB6BAgGEBc&adurl=) |
| **MG995 Servo Motor (for Neck)** | 2 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwiA_IbJpM-SAxWlqGYCHd16Mq8YACICCAEQDBoCc20&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgl2wCCCcUO1-TpGcpyFQvpYHgbEHKhzRqCi6t94odldZCJ8lLduMx8aApXdEALw_wcB&cid=CAAS0wHkaL9hbVCluVLg4jxYzZ1EdIMau7kXFVopDIX4vJgYzyXDAjUQ6K8x1Xs9FWcCN72Zj8UiBRiBWLb5qT3Vwt6GyNTgYaieTYj9HQYNNbtHgLcGIwWm2leW8XpVbp6CnlJyBAfmgA0477BZrroS_v7Aq1yGQSvIAMrXM2TaaxVrHOC8YBU3QZEdlzXpdTVN4SvJHIKvZQNgL96yHUzOpFQenP-D81Q_biqX_hD5bDCFJcRYPVTJMfLoCa7Q6n9FnM6ltPj61QkASjToqOulBCnmmiQo&cce=2&category=acrcp_v1_32&sig=AOD64_1yil5cQUQqXfDGbgJQJB7q5-W1bQ&ctype=5&q=&nis=4&ved=2ahUKEwiMq_7IpM-SAxXn3jgGHUfgF80Q5bgDKAB6BAgHEBM&adurl=) |
| **MG90S Servo Motor (for Antenna & Dispensor)** | 4 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwiA_IbJpM-SAxWlqGYCHd16Mq8YACICCAEQEBoCc20&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgkKHMhf9VS0jlqx6y02sNmLjrgMajRkB7_1hNEVcT1jZZ6wCLAXeXEaAr3CEALw_wcB&cid=CAAS9gHkaIdgbcN34nLIjCsiYfGILNSvWX68CywEw6u8mH1kd2VrO1iBkK97u0Q9JU2liwVBymcDEBnsp9rdpY6NqQuKlvszjgE7pnheL1g-J4RT0sclrQIdwZXsDosb0e_pZGAvrcPBmHBVYIINZDBw_20f3l6_qOuoVpnnIiWe8vacN8qbl1Wtmy3KuCshMtUfn78046PsaQSKp9IYa8otoi2akApXfVBfnzX6eL3Wwe4audt6-8CX7dpFgZexQ3nlxlYVNy6AizRCtUxNYmQabT4WS2aAYmbFMsSFAW3uncewXpE_A218yejGCK_eLXZB0jiBDnRR7Ks&cce=2&category=acrcp_v1_32&sig=AOD64_0tLCgAJysRscgk8-5EtrjfXB0PIA&ctype=5&q=&nis=4&ved=2ahUKEwiMq_7IpM-SAxXn3jgGHUfgF80Q5bgDKAB6BAgHEA8&adurl=) |
| **Arduino nano (to expand Pins)** | 2 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwjD65m_ps-SAxWJuCkDHaHYNxQYACICCAEQCRoCdGI&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgmzkxnas7eT9BUOn2odhz3GDFBZbdpfahqy9N4LZ1oLT4chLITouyoaAkuzEALw_wcB&cid=CAAS9gHkaBnRJIAv4NSlU0BtLEjPG_x6zoCRh0bajtZEo9SFSkKqUik34ppMX3dqmKxx2xSUlfCMoNb1SXfdYH3jIIa8i1TP8qFidDPoB4LTv-xwiImw0rDXYc19VSSJxB5oUBMlYLzpRVvHQm3DHK4dZFCYxx756UBiMzSf5f1n54BYhXS5dMsWw7iBpiUglVuRrfacApIvhrjaq5Avdvi0pUMqDdmy_RiGQLY3bzLn4w-UJGnBPRYFy0svuZi90iR8Iy8ZPxhIzT5kTbV3--tG9QaI4gkXY2vwTjjSeNpuHW2Bi9nLb-6nouo73zojJ8bIeNIINpJpu3g&cce=2&category=acrcp_v1_32&sig=AOD64_0VA_2AzJJ6oCFxKcN8ybXdwZVQog&ctype=5&q=&nis=4&ved=2ahUKEwici5K_ps-SAxXpc_UHHctrMzAQ5bgDKAB6BAgJEB8&adurl=) |
| **24 Awg Wires bundle 5 meter** | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwiKkq7fps-SAxXwaw8CHRw2HZIYACICCAEQEhoCdGI&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgmRnwJpgZr_g1VrEluhgyT5rwMgwZ2rhC8ZM005mhyeyaDa1DPECgYaAibZEALw_wcB&cid=CAAS9gHkaJi4wzTLga9YJ2cTWBY7wuIk3GSE96zb2X_4oGE9kmmPErZD3I4MvoJT0xN8ZzVHOOzG5hPBExC87HaoRn1qFDh7hwEYVbnLRKmr4pU7i2Wfd8za53ukS0FcLu2B9T5yXj5owfgZyEI2k8CvRSUtYUEQ3o7SGVssaVCH_qn3B-QrCuamHvSRY1r7Hva4mwZcXrXM0Y_Q_5ko3kXPyqynu9vUL8j_TznhTtnxLItopQWdU0wjKNiGTd2Ekj8suJ1PsmvL1Unl7cdZ2h1iN74W7c6yd7QNo95HaN4CNGgNB4WFgnlWOEKB-dTOzkhAvcb6eSQe8UE&cce=2&category=acrcp_v1_32&sig=AOD64_26lMbOcxxnI000zgAWy8gQtqAOeg&ctype=5&q=&nis=4&ved=2ahUKEwintabfps-SAxU1iK8BHVtfJ3YQ5bgDKAB6BAgLEBc&adurl=) |
| **eSun PLA+ 1.75mm (Color depends on your Choice)** | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwjf2bKVp8-SAxXBLXsHHQMuPHoYACICCAEQDBoCdG0&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOglmmLtjJmZciyNl89-lBIen8V-ZzCnBAexf2orb1MWalVd9HY-sceYaAr2gEALw_wcB&cid=CAAS9gHkaEz1cKUcR9JCx2CbJD3LpH3i8s2cJMh2zU531PbZlYzIXlOZt-yXwIfdJan0rs0N3_vpqM8a48qIAWjba-k_GXeDGgUGwOlProaM027I8Oo3H5GfCYYS5LKK_fXzih8AQLDdUHDF93uFMxzpTgrw-qQ0msco4OcNMik7Yhb5jUW0w5wTOqmGici5m-NXTxneAio5WdUHEq3S2utfgv651cWJpOFyS0oRalpxcaz6TTHX9wi8IDpActLuIPjMMSnLxipecP-_IwIx3x9uEZ3dwMyfVlQIWwA9wzNy7cCWE5X66KTJaRwZLgkOK0W7d2Lin6tqHrg&cce=2&category=acrcp_v1_32&sig=AOD64_2K-FkpZ8EpTG427DAfOHZgNnd2rw&ctype=5&q=&nis=4&ved=2ahUKEwjX6amVp8-SAxV1iK8BHY7lOgsQ5bgDKAB6BAgMEAs&adurl=) |
| **Soldering Iron (Recommended all Tools Are included in this))** | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwjy0pm-p8-SAxX2JXsHHXHoI98YACICCAEQDhoCdG0&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOglEP88SlmA600q5_XQnvQkF_GeGnwhTYXV-mesPNbQe4H9QdJA1wIcaAlAbEALw_wcB&cid=CAAS9gHkaD9nNaMGrA9Esmqo7YmGaPeIk82s89ajFJYh4y18-ZNWqw7JqxNoy5AfVQoPpVbwjArBCfmVDR0R80yRjpD8Q24aXuu8GpVd_EZcBk672f_iWhDYJqirJ1DGYMCv80zHICLlEg9fq4IREMUgQKcwgTM8YHltNm32qbHNrdtpXXuITxE0Dt6U4RnxD51zXi61zUS64ZqYYkuNV-OpVwFC21ZJ3Ve--QOy8jb6r9bCBbmbzD7UfgwRtR9NUbjBED5lJqDLOE49vxjXfCQpovGFpP_I0HP-mOXhojAKs56wNSo9cF1Px6hz7DVkb9bjZYmAcHOviwU&cce=2&category=acrcp_v1_32&sig=AOD64_0DI5KFb9102hNmpZNUV0HYWI5b5g&ctype=5&q=&nis=4&ved=2ahUKEwjtlZG-p8-SAxXpcfUHHZnhAnIQ5bgDKAB6BAgGEAs&adurl=) |
| **Glue Gun** | 1 | [Buy Here](https://www.meesho.com/glue-guns/pl/997?srsltid=AfmBOor-x8Y_ux-g0ucn7r0g1IZt1v4XrUss-9I_4eg-g9kcGDKD0NQX) |
| **ESP32 Wroom DA** | 1 | [Buy Here](https://robu.in/product/esp-wroom-32-esp32-wifi-bt-ble-mcu-module/) |
| **4 Channel Relay (5v)** | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwizhqSXwM-SAxU8yxYFHZLvLSAYACICCAEQBBoCdGw&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgn__FjLbJv8w-fDeQr9gRb-lIsL7-xEagmBH36pWsqnSK_hBafLYsEaAutAEALw_wcB&cid=CAAS0wHkaM2qlPJEKUW7MhNhsyzAhffEVkZtOrAVwMbb47Y6KQLOnZKPrYdpPEsI2nEj58xULg8UrSYsWYKepXj4TDiTcYiQc9qIdbGgCPCqVVtizyF2YhCJa7aFcLs7p5xFHlGxhdHXeniOdjZcLWuoEMAc0xBbUmIvRpM-yOdBi_v_xPFPQhNH50G4gMuPCkhL4WX8E3rfSZDY2FvNKuPirLKfURUj6XWMUB3Ss4CisnkTikR8z-dPAqgWEj-V8bR65FJWrA4aw3oSZaEbkOuC_7486WPS&cce=2&category=acrcp_v1_32&sig=AOD64_21dEYCZANBEndh4eV1PdneoSS99g&ctype=5&q=&nis=4&ved=2ahUKEwiYz5yXwM-SAxVa1jQHHShyKSsQ5bgDKAB6BAgKEA8&adurl=) |
| **li-ion Battery Pack (12v) Recommended** | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwjnqKGaws-SAxWl9RYFHZC9H3MYACICCAEQERoCdGw&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgnpnegFMGi_7gzyuEL8FJwIEjHA2xbl6U5hJ7olnx9G_4ks0nEsAi4aAnHxEALw_wcB&cid=CAAS9gHkaCXwQfSMBGvNICHGlJaTHpmh5nJV7vLwRZjdFyVmrYWHdz5mh17BbxYucNWOYTV_OiDAW1EHsjktOGsI88SIovN-012RIWMvVovoDmP0e-O3T77V_wU5yetf7v0_oQNJbThnvNqs8IdklqEKgIqY6YEd-QTYnayw9QHFXjSIetTBLaJx6TiD9-mBvPETojdC4dm88RrUENT02x00QQvMX4pRwdGJ55EC4r7X4g2tuYrwy6-p4nCJDYcjFpk9UZNgdr6LRUU4WddAR-K8nWO2nL35kYkJZOvLqKAAq2Pm3EzlToX9XkHGiuoJuA8lqQy2_N6gIvA&cce=2&category=acrcp_v1_32&sig=AOD64_35vR8sJ3yKJXrUWyt12X8SoeOAAQ&ctype=5&q=&nis=4&ved=2ahUKEwiQqZmaws-SAxV2rVYBHQXKDAsQ5bgDKAB6BAgJECQ&adurl=) |
| **Wall Adapter (5V 4amp)** | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwjdqqzkws-SAxXjhrkFHSFpMX4YACICCAEQBRoCdG0&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOgnxsTD2MxSGVaHq1-YjUUxpHclJyjPB3gMr-6fP2NU9BSG6qZcqGRoaAuqVEALw_wcB&cid=CAAS9gHkaIyFgBlG9L1F24j40iIaD9ny7mC-4I_POyCWim66mc8P1BYQKJGsn73HGb_W3p7kUwY8ei6ZtsVoA2Isd1eGiLLgPtI7ydJm95YhvM735Dqhhsp67xVoX73Y6QM0ejIkpiSegGC8nwVAr-QBBvpIdT7Yq9ZNNx3C8JUAmaGBeBOhcbV4MMc87znliU3MR_wlX7Qy01Vlz9KbkMF3h-YTc8Kes7C8siez2xTTCKn6pzox_vaql2Sfydw3Oz84EhmsHKWVSb4PpCBICcx5q35dUoZxHhdtXhm_1iuSk71bVJGiDZVLFu2wRCCPqvpFkvfuJSVJFx0&cce=2&category=acrcp_v1_32&sig=AOD64_3Ktyg4BCTMooL7cjwtEnqvpNVU9w&ctype=5&q=&nis=4&ved=2ahUKEwik06Tkws-SAxWIqVYBHf3VBHAQ5bgDKAB6BAgFEBA&adurl=) |
| **Screw Driver Set** | 1 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwjby9Wjw8-SAxUDmLkFHYDNLU4YACICCAEQBRoCdG0&co=1&ase=2&gclid=Cj0KCQiAy6vMBhDCARIsAK8rOglp8R36W2eyosTGg918C-qDzsBbZ72r9_jM63IDiJM-WsRxULd7_rcaAr8XEALw_wcB&cid=CAAS9gHkaKtnzf8x9TJMX3Qt4sceCivcRyjhqwON41lRwQLzTXW-josz0_doaehhlecfQlm5B5Gbnd843e-7FVjGI4CDzGyrk4JJEUoS1FrNPw4W6YdSSo82cTyjOIIOHDvlP5E997h4NRpIDpj4BcRVhQeGsh_nzTGDSwM5X2FQJ33ZdfQK3XLNkYxg9VdtToFae82hWi2h3htmef4Pmxc7u6FH-8A-sRYcdraItOyH2aaScELwNc7VSGwljv31aIITsf4RqSRcfjOiGjg4IIbRreJ1XzBf7Ivet1Qpu9A0o8cj3taNErFOB_WLhHGg1uv2NWOdBvOD-BI&cce=2&category=acrcp_v1_32&sig=AOD64_2IV3b3rbL4p2gLKxzZ6xiMl0Osog&ctype=5&q=&nis=4&ved=2ahUKEwjrls6jw8-SAxUnr1YBHdBsJhoQ5bgDKAB6BAgFEA8&adurl=) |
| **Wire Cutter** | 1 | [Buy Here](https://kitsguru.com/products/economy-precision-flush-cutter-pcb-wire-nipper-cutting-tool?variant=48591803941116&country=IN&currency=INR&utm_medium=product_sync&utm_source=google&utm_content=sag_organic&utm_campaign=sag_organic&srsltid=AfmBOooVkUzRcXpzuAR8L-lYS0JHtCNQreehoGTBw4gAmpKR5jyaeGkyfRw) |
| **DT830D Multimeter** | 1 | [Buy Here](https://robu.in/product/digital-multimeter-small-yellow-color-lcd-ac-dc-measuring-voltage-current/) |
| **M4x8mm Screws** | 8 | [Buy Here](https://www.google.com/aclk?sa=L&ai=DChsSEwiFl7_oxdKSAxWWpmYCHT5uKk4YACICCAEQFxoCc20&co=1&ase=2&gclid=Cj0KCQiA7rDMBhCjARIsAGDBuEAlQGzAZw0qdem7-60RNQTOT9dNPo6ykoIa4cxmq4PgOs9AnO_VPZsaApwIEALw_wcB&cid=CAAS0wHkaDrtpdPDzT8eAJFteGg9GsbXG6jPiPOHJ-KTtoZaOPOs_8sBrSd1u6q8nRABgkoGZIjqerokGcEXLuWtTRwS8_RlfHFiwiSp9cpPbfJDTV1AP025ihbMH0fil_tkndXsgKOXgEI9urFq8f_jCqZ6w3d2vdMmKCu09Juvdmuig3vcRH8iKE2tn41WeLsnkxwYT6cfz2LSHIwzpGTtyD8Wp959QHr3ICj7kXq2nIfW-GTDgYWx3lM_hM-gh0CFRACVbjeoTngKsZuwv5qZQ0KS2iGi&cce=2&category=acrcp_v1_32&sig=AOD64_1GtmLVPU2Hxh4FOlbq2U59gB3gYg&ctype=5&q=&nis=4&ved=2ahUKEwjPyLfoxdKSAxX-UGwGHSrjLBcQ5bgDKAB6BAgKECA&adurl=) |

---

## 📚 Software Infrastructure & Libraries

To compile and upload the code, you **must** install the following libraries in your Arduino IDE.

### 1. Required Libraries
| Library Name | Purpose | Implementation |
| :--- | :--- | :--- |
| **MD_MAX72XX** | Handles the 8x8 LED Matrix display for the eyes. | `head_arduino_0x09.ino` |
| **Servo** | Controls the PWM signals for neck and dispenser motors. | All modules |
| **Wire** | Enables I2C communication between the Master and Slaves. | `Base` & `Head` |
| **WiFi & WebServer** | Enables ESP32 to act as a local IoT server. | `esp32_relay_module.ino` |

### 2. Step-by-Step Installation
1.  Open **Arduino IDE**.
2.  Go to **Tools** -> **Manage Libraries...** 
3.  In the search bar, type `MD_MAX72XX` and click **Install**.
4.  The `Servo`, `Wire`, `WiFi`, and `WebServer` libraries are usually built-in. If missing, search for them individually and install the versions by **Arduino** or **Espressif**.
5.  **ESP32 Board Support**: 
    - Go to `File` -> `Preferences`.
    - In "Additional Boards Manager URLs", paste: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`.
    - Go to `Tools` -> `Board` -> `Boards Manager`, search for `esp32` and install.

---

## 🧠 Deep Dive: How the Code Works

The project is split into three core logic modules that communicate over a shared **I2C Bus**.

### 1. Base Controller (`0x08.ino`)
*   **The Logic**: Acts as the "Motor Cortex." It manages physical movement and timing.
*   **Movement Engine**: Uses a smoothing algorithm (`currentPos += (target - currentPos) * 0.1`) to ensure the neck doesn't snap abruptly, creating "alive-like" idle motions.
*   **Dispensing System**: A simple loop blocks I2C for a few seconds during a dispense cycle to ensure mechanical accuracy.

### 2. Head Controller (`0x09.ino`)
*   **The Logic**: Acts as the "Emotional Engine." It translates byte-arrays into facial expressions.
*   **Eye Patterns**: Expressions like `SAD`, `HAPPY`, and `SECURE` are stored as 8-byte hexadecimal arrays. The code updates these columns at high speed to create animations.
*   **Blink Logic**: A randomized timer triggers a "closed eye" pattern for 150ms every 2-5 seconds, simulating human-like behavior.

### 3. ESP32 Relay Module (`esp32_relay.ino`)
*   **The Logic**: Acts as the "Communication Gateway."
*   **REST API**: It maps specific URL paths (like `/light_on`) to GPIO toggles. When you visit the IP address, it serves a lightweight HTML page with buttons that trigger these endpoints.

---

## 🚀 Step-by-Step Setup & Upload

### Phase 1: Preparation
1.  **Wiring**: Connect all SDA pins together and all SCL pins together. Ensure a **Common Ground** between the Nano and ESP32.
2.  **Power**: Plug your 12V battery into the Buck Converter. Tune the converter to exactly **5.0V** before connecting to the Arduinos.

### Phase 2: Uploading Code
1.  **Base (Nano #1)**:
    - Open `Base_trigger.ino`.
    - Select Board: `Arduino Nano` (Processor: `ATmega328P (Old Bootloader)` is common).
    - Upload. Note: This device sits at I2C address `0x08`.
2.  **Head (Nano #2)**:
    - Open `head_arduino_0x09.ino`.
    - Upload to the second Nano. This device sits at I2C address `0x09`.
3.  **IoT Hub (ESP32)**:
    - Open `esp32_relay_module.ino`.
    - **Crucial**: Change lines 4 & 5 to your WiFi Name and Password.
    - Select Board: `ESP32 Dev Module`.
    - Upload. Open the Serial Monitor at 115200 baud to find the **IP Address**.

---

## 🐛 Troubleshooting & Common Errors

### 1. Hardware Issues
*   **"Servos are twitching or the board resets when they move"**
    - **Cause**: Current starvation. Servos can pull 1A+ each when stalled.
    - **Fix**: Use a dedicated 5V 4A supply. Do NOT power servos from the Nano's 5V pin.
*   **"I2C devices not found or data is corrupted"**
    - **Cause**: Missing pull-up resistors or floating ground.
    - **Fix**: Ensure GND is shared. Add two 4.7kΩ resistors between SDA-5V and SCL-5V if the bus is long.

### 2. Software Issues
*   **"Matrix is showing garbage or mirrored text"**
    - **Cause**: Incorrect `HARDWARE_TYPE`.
    - **Fix**: In `head_arduino_0x09.ino`, change `FC16_HW` to `GENERIC_HW` or `ICSTATION_HW` until it looks correct.
*   **"ESP32 won't connect to WiFi"**
    - **Cause**: 5GHz network or wrong credentials.
    - **Fix**: Ensure your router supports 2.4GHz. Triple-check the password in the code.

### 3. Logic Errors
*   **"Dispenser moves but doesn't stop"**
    - **Cause**: Potentiometer setting in MG90S (if modified) or logic interference.
    - **Fix**: Check `DISP_MIN` and `DISP_MAX` values in `Base_trigger.ino`.

---

> **Built with ❤️ for the Memento Board By Adafruit Project**  
> (image={Final assembly photo of the Digi-Home system})
