void listAll(string path, const Class* c)  // two-parameter overload
{
    if (c == nullptr) return;
    cout << path + c->name() << '\n';
    for (auto it=c->subclasses().begin(); it!=c->subclasses().end(); it++) {
        listAll(path + c->name() + "=>", *it);
    }
}
