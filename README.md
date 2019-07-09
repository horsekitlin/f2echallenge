# create react app reason

## initial command line

```
$ yarn create react-app f2echallenge2 --scripts-version reason-scripts
```

## bsconfig.bs.js

### Source

```json
{
  "name": "reason-scripts",
  "sources": ["src"],
  "bs-dependencies": ["reason-react", "@glennsl/bs-jest", "bs-fetch"],
  "reason": {
    "react-jsx": 2
  },
  "refmt": 3,
  "package-specs": {
    "module": "commonjs",
    "in-source": true
  },
  "suffix": ".bs.js"
}
```

update to

```json
{
  "name": "reason-scripts",
  "ppx-flags": [],
  "sources": {
    "dir" : "src",
    "subdirs" : true
  },
  "bs-dependencies": ["reason-react", "@glennsl/bs-jest", "bs-fetch"],
  "reason": {
    "react-jsx": 3
  },
  "refmt": 3,
  "namespace": true,
  "package-specs": {
    "module": "commonjs",
    "in-source": true
  },
  "suffix": ".bs.js"
}
```

css framework
  - mini.css