import Functions


def validate_addition():
    assert Functions.addition_in_base_h('11100111001110101', '1101111011111', 2) == '11110101001010100'
    assert Functions.addition_in_base_h('23045', '100254', 6) == '123343'
    assert Functions.addition_in_base_h('54AB6F', 'CD097D', 16) == '121B4EC'
    assert Functions.addition_in_base_h('2122012', '10112222', 3) == '20012011'
    assert Functions.addition_in_base_h('3220013', '22303231', 4) == '32123310'
    assert Functions.addition_in_base_h('3401323', '444033', 5) == '4400411'
    assert Functions.addition_in_base_h('6543210', '664455', 7) == '10540665'
    assert Functions.addition_in_base_h('5677034', '1234567', 8) == '7133623'
    assert Functions.addition_in_base_h('ABCDE', 'D9037F', 16) == 'E3C05D'
    assert Functions.addition_in_base_h('1100101011', '11101101', 2) == '10000011000'


def validate_subtraction():
    assert Functions.subtraction_in_base_h('10001100010', '1110111011', 2) == '10100111'
    assert Functions.subtraction_in_base_h('102387', '64502', 9) == '26785'
    assert Functions.subtraction_in_base_h('501BA', '32ED', 16) == '4CECD'
    assert Functions.subtraction_in_base_h('130046', '71257', 8) == '36567'
    assert Functions.subtraction_in_base_h('210354', '55466', 7) == '121555'
    assert Functions.subtraction_in_base_h('210354', '44355', 6) == '121555'
    assert Functions.subtraction_in_base_h('102003', '3333', 5) == '43120'
    assert Functions.subtraction_in_base_h('102003', '3333', 4) == '32010'
    assert Functions.subtraction_in_base_h('100111000', '1100111', 2) == '11010001'
    assert Functions.subtraction_in_base_h('10B009', 'A5FCD', 16) == '6503C'


def validate_multiplication():
    assert Functions.multiplication_in_base_h('7023', '5', 8) == '43137'
    assert Functions.multiplication_in_base_h('32001B', '6', 16) == '12C00A2'
    assert Functions.multiplication_in_base_h('12345', '5', 7) == '65424'
    assert Functions.multiplication_in_base_h('12345', '5', 6) == '111101'
    assert Functions.multiplication_in_base_h('31203', '3', 5) == '144114'
    assert Functions.multiplication_in_base_h('31203', '3', 4) == '220221'
    assert Functions.multiplication_in_base_h('21563', '7', 8) == '174045'
    assert Functions.multiplication_in_base_h('A23F4', 'B', 16) == '6F8B7C'


def validate_division():
    assert Functions.division_in_base_h('20101', '2', 3) == ('10012', 0)
    assert Functions.division_in_base_h('1FED0205', '9', 16) == ('38C1CAB', 2)
    assert Functions.division_in_base_h('120456', '6', 8) == ('15335', 0)
    assert Functions.division_in_base_h('120456', '6', 7) == ('13421', 0)
    assert Functions.division_in_base_h('321023', '3', 5) == ('103322', 2)
    assert Functions.division_in_base_h('321023', '3', 4) == ('103003', 2)
    assert Functions.division_in_base_h('2A0F86', 'E', 16) == ('3011B', 'C')
    assert Functions.division_in_base_h('765433', '4', 8) == ('175306', 3)
