Build instructions for the impatient


```bash
curl https://raw.githubusercontent.com/centreon-deb/centreon-connectors/debian/bootstrap | sh
cd centreon-connectors && git deb-pkg -C -U -u 1.1.1 -d origin/debian build
```

Further instruction in the [README.Build.md](README.Build.md) file.
