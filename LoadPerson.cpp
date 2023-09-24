struct DBSettings {
    string db_name;
    int db_connection_timeout;
    bool db_allow_exceptions;
    DBLogLevel db_log_level;
};

struct QueryParams {
    int min_age;
    int max_age;
    string name_filter;
};

string QueryStr(const DBHandler& db, const QueryParams querypar) {
    ostringstream query_str;

    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << querypar.min_age << " and "s << querypar.max_age << " "s
              << "and Name like '%"s << db.Quote(querypar.name_filter) << "%'"s;

    return query_str.str();
}

vector<Person> LoadPersons(DBSettings dbset, QueryParams querypar) {
    DBConnector connector(dbset.db_allow_exceptions, dbset.db_log_level);
    DBHandler db;

    if (dbset.db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(dbset.db_name, dbset.db_connection_timeout);
    } else {
        db = connector.Connect(dbset.db_name, dbset.db_connection_timeout);
    }
    if (!dbset.db_allow_exceptions && !db.IsOK()) {
        return {};
    }

    DBQuery query(QueryStr(db, querypar));

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({move(name), age});
    }
    return persons;
}
