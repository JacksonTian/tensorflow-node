TESTS = test/*.js
REPORTER = spec
TIMEOUT = 20000
MOCHA = ./node_modules/mocha/bin/_mocha
PATH := ./node_modules/.bin:$(PATH)

lint:
	@eslint --fix lib index.js test

build:
	@node-gyp rebuild

install:
	@cnpm install

test: build
	@mocha -t $(TIMEOUT) -R spec $(TESTS)

test-cov: build
	@nyc --reporter=html --reporter=text mocha -t $(TIMEOUT) -R spec $(TESTS)

test-coveralls: build
	@nyc mocha -t $(TIMEOUT) -R spec $(TESTS)
	@echo TRAVIS_JOB_ID $(TRAVIS_JOB_ID)
	@nyc report --reporter=text-lcov | coveralls

.PHONY: test build
