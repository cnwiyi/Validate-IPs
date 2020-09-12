This Program validate if a passed in IP is a valid IPv4 IP.

Sample:
    Enter IP to validate: 10.181.82.73
    Yes IP is valid (10.181.82.73)

    Terminate Program? (y/n): n
    Enter IP to validate: 10.300.1.78
    Invalid IP (10.300.1.78) due to IPv4 format error: Octet over 255.

    Terminate Program? (y/n): n
    Enter IP to validate: 15.A5.4F.12E.21
    Invalid IP (15.A5.4F.12E.21) due to IPv4 format error: Special character found in IP (Valid: 0-9 and Periods).

    Terminate Program? (y/n): y
    Program Terminated!

Validates and returns errors. Called in a loop until terminated.