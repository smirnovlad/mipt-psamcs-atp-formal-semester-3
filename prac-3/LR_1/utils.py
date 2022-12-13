from __future__ import annotations
from typing import Set


class Rule:
    def __init__(self, left: str, right: str) -> Rule:
        self.left = left
        self.right = right

    def __eq__(self, other: Rule) -> bool:
        if isinstance(other, Rule):
            return (self.left == other.left) and (self.right == other.right)
        return False

    def __hash__(self) -> int:
        return hash((self.left, self.right))


class Grammar:
    def __init__(self, nonterms: Set[str], terms: Set[str]) -> Grammar:
        self.nonterms = nonterms
        self.terms = terms
        self._rules = set()

    def add_rule(self, rule: Rule) -> None:
        self._rules.add(rule)

    def is_terminal(self, letter: str) -> bool:
        return letter in self.terms

    def rules(self) -> Set[Rule]:
        return self._rules
