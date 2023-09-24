void CheckYear(const DateTime& dt) {
    if (dt.year < 1) {
        throw domain_error("year is too small"s);
    }
    if (dt.year > 9999) {
        throw domain_error("year is too big"s);
    }
}

void CheckMonth(const DateTime& dt) {
    if (dt.month < 1) {
        throw domain_error("month is too small"s);
    }
    if (dt.month > 12) {
        throw domain_error("month is too big"s);
    }
}

void CheckDay(const DateTime& dt) {
    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (dt.day < 1) {
        throw domain_error("day is too small"s);
    }
    if (dt.day > month_lengths[dt.month - 1]) {
        throw domain_error("day is too big"s);
    }
}

void CheckHour(const DateTime& dt) {
    if (dt.hour < 0) {
        throw domain_error("hour is too small"s);
    }
    if (dt.hour > 23) {
        throw domain_error("hour is too big"s);
    }
}

void CheckMinute(const DateTime& dt) {
    if (dt.minute < 0) {
        throw domain_error("minute is too small"s);
    }
    if (dt.minute > 59) {
        throw domain_error("minute is too big"s);
    }
}

void CheckSecond(const DateTime& dt) {
    if (dt.second < 0) {
        throw domain_error("second is too small");
    }
    if (dt.second > 59) {
        throw domain_error("second is too big"s);
    }
}

void CheckDateTimeValidity(const DateTime& dt) {
    CheckYear(dt);
    CheckMonth(dt);
    CheckDay(dt);
    CheckHour(dt);
    CheckMinute(dt);
    CheckSecond(dt);
}
